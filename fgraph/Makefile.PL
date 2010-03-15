#!/usr/bin/perl

use warnings;
use strict;
use Carp;
use File::Find::Rule;
use File::Copy;
use File::Util;
use File::Path;
use File::Slurp;
use TAP::Harness;
use Cwd;
use JSON;
use Pod::Man;

#set our c flags
my $CFLAGS = '-Wall -g -ltap';
my $CC = 'gcc';

main();

sub main {
    if(!defined($ARGV[0]) || $ARGV[0] eq '') {
        none();
        exit(0);
    }
    
    if($ARGV[0] eq 'test') {
        none();
        exit(test());
    }
    
    if($ARGV[0] eq 'install') {
        none();
        install();
        exit(0);
    }
    
    if($ARGV[0] eq 'clean') {
        clean();
        exit(0);
    }
    
    if($ARGV[0] eq 'dist') {
        dist();
        exit(0);
    }
    
    Carp::croak('No such target '.$ARGV[0]);
}

sub none {
    #check if build dir exists
    if(!(-e 'build' && -d 'build')) {
        if(!-e 'build') {
            print "mkdir build\n";
            mkdir('build');
        }
        
        if(!-d 'build') {
            Carp::croak('build is not a directory!');
        }
    }
    
    #src
    copydir('src', 'build', qr/.+\.c|.+\.h/);

    #t
    copydir('t', 'build', qr/.+\.c/);

    #doc
    copydir('doc', 'build', qr/.+\.pod/);

    #compile everything in build/src
    compiledir('build/src', qr/.+\.c/, '.o', '');

    #copy tap.o and tap.h to build/t
    print 'cp ', 'build/src/fgraph.h', ' ', 'build/t/fgraph.h', "\n";
    copy('build/src/fgraph.h', 'build/t/fgraph.h') || Carp::croak("Could not copy header file: $!");
    print 'cp ', 'build/src/fgraph.o', ' ', 'build/t/fgraph.o', "\n";
    copy('build/src/fgraph.o', 'build/t/fgraph.o') || Carp::croak("Could not copy object file: $!");
}

sub test {
    #compile all the tests against
    #build/t/tap.h and tap.o
    my @tests = compiledir('build/t', qr/.+\.c/, '', 'build/t/fgraph.o');
    @tests = sort @tests;
    my $th = TAP::Harness->new({'exec' => []});
    my $agg = $th->runtests(@tests);
    return 1 if $agg->get_status() =~ /FAIL/;
    return 0;
}

sub install {
    #if install is set, install into
    #/usr/include/tap.h and /usr/lib/tap.o
    my $cfg = read_config();
    if(!defined($cfg->{'config'}->{'name'})) {
        Carp::croak('Name not defined');
    }
    
    if(!defined($cfg->{'config'}->{'abstract'})) {
        Carp::croak('Abstract not defined');
    }
    
    if(!defined($cfg->{'config'}->{'version'})) {
        Carp::croak('Version not defined');
    }
    
    if(!defined($cfg->{'config'}->{'repository'})) {
        Carp::croak('Repository not defined');
    }
    
    if(!defined($cfg->{'config'}->{'author'})) {
        Carp::croak('Author not defined');
    }
    
    if(!defined($cfg->{'config'}->{'copyright_holder'})) {
        Carp::croak('Copyright holder not defined');
    }
    
    if(!defined($cfg->{'config'}->{'license'})) {
        Carp::croak('License not defined');
    }

    #manify our docs
    #replace the placeholders with the appropriate values
    my $pod = read_file('build/doc/fgraph.pod');
    
    #version
    $pod =~ s/\$VERSION\$/$cfg->{'config'}->{'version'}/;
    
    #repository
    $pod =~ s/\$REPOSITORY\$/The source code repository for this project is located at:\n\n  $cfg->{'config'}->{'repository'}/;
    
    #author
    if(ref($cfg->{'config'}->{'author'}) eq 'ARRAY') {
        my $author = join("\n  ", @{$cfg->{'config'}->{'author'}});
        $author = '  '.$author;
        $author =~ s/\s+$//;
        $pod =~ s/\$AUTHOR\$/$author/;
    } else {
        $pod =~ s/\$AUTHOR\$/  $cfg->{'config'}->{'author'}/;
    }
    
    #copyright
    my @td = localtime();
    my $copyright = 'This software is Copyright (c) '.($td[5]+1900).' by '.$cfg->{'config'}->{'copyright_holder'}.".\n\n";
    $copyright .= 'This is free software, licensed under:'."\n\n";
    if($cfg->{'config'}->{'license'} eq 'MIT') {
        $copyright .= '  The MIT (X11) License';
    } elsif($cfg->{'config'}->{'license'} eq 'BSD') {
    $copyright .= '  The Simplified BSD License';
    } else {
        Carp::croak('Unsupported license type');
    }
    $pod =~ s/\$COPYRIGHT\$/$copyright/;
    
    write_file('build/doc/libtap.pod', $pod) || Carp::croak('Could not replace special configuration values in POD');
    
    my $p2m = Pod::Man->new('center' => $cfg->{'config'}->{'name'}.': '.$cfg->{'config'}->{'abstract'},
                            'name' => $cfg->{'config'}->{'name'},
                            'release' => $cfg->{'config'}->{'version'}
                            );
    $p2m->parse_from_file('build/doc/fgraph.pod', 'build/doc/fgraph.1');
    print "pod2man build/doc/fgraph.pod build/doc/fgraph.1\n";
    copy('build/doc/fgraph.1', '/usr/local/man/man1/fgraph.1') || Carp::croak("Could not install man: $!");
    print "cp build/doc/fgraph.1 /usr/local/man/man1/fgraph.1\n";

    #compile and copy into install dirs
    copy('build/src/fgraph.h', '/usr/include/fgraph.h') || Carp::croak("Could not install fgraph.h: $!");
    print "cp build/src/fgraph.h /usr/include/fgraph.h\n";
    system(join(' ', ($CC, '-Wall -O2 -fPIC -c build/src/fgraph.c -o build/src/fgraph.o')));
    print join(' ', ($CC, '-Wall -O2 -fPIC -c build/src/fgraph.c -o build/src/fgraph.o')), "\n";
    system(join(' ', ($CC, '-Wall -O2 -shared -Wl,-soname,libfgraph.so.1 -o build/src/libfgraph.so.1.0.0 build/src/fgraph.o -lc')));
    print join(' ', ($CC, '-Wall -O2 -shared -Wl,-soname,libfgraph.so.1 -o build/src/libfgraph.so.1.0.0 build/src/fgraph.o -lc')), "\n";
    copy('build/src/libfgraph.so.1.0.0', '/usr/lib/libfgraph.so.1.0.0') || Carp::croak("Could not install libfgraph.so.1.0.0: $!");
    print "cp build/src/fgraph.so.1.0.0 /usr/include/libfgraph.o\n";
    symlink('/usr/lib/libfgraph.so.1.0.0', '/usr/lib/libfgraph.so.1');
    print 'ln -s /usr/lib/libfgraph.so.1.0.0 /usr/lib/libfgraph.so.1', "\n";
    symlink('/usr/lib/libfgraph.so.1.0.0', '/usr/lib/libfgraph.so');
    print 'ln -s /usr/lib/libfgraph.so.1.0.0 /usr/lib/libfgraph.so', "\n";
}

sub clean {
    #rm -rf build
    print "rm -rf build\n";
    rmtree('build');
    
    my $cfg = read_config();
    if(defined($cfg->{'config'}->{'name'}) && defined($cfg->{'config'}->{'version'})) {
        if(-e $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}) {
            print 'rm -rf ', $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}, "\n";
            rmtree($cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'});
        }
        
        if(-e $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'.tar.gz') {
            print 'rm ', $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'.tar.gz', "\n";
            unlink $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'.tar.gz';
        }
    }
}

sub dist {
    #make ourselves a distribution
    my $cfg = read_config();
    if(!defined($cfg->{'config'}->{'name'})) {
        Carp::croak('Name not defined');
    }
    if(!defined($cfg->{'config'}->{'version'})) {
        Carp::croak('Version not defined');
    }
    
    if(-e $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}) {
        print 'rm -rf ', $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}, "\n";
        rmtree($cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'});
    }
    
    if(-e $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'.tar.gz') {
        print 'rm ', $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'.tar.gz', "\n";
        unlink $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'.tar.gz';
    }
    
    mkdir($cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'});
    print "mkdir ", $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}, "\n";
    
    copydir('src', $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}, qr/.+\.h|.+\.c/);
    copydir('t', $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}, qr/.+\.c/);
    copydir('doc', $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}, qr/.+\.pod/);
    copydir('examples', $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}, qr/.+\.c/);
    
    create_authors($cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'/AUTHORS');
    create_license($cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'/LICENSE');
    create_readme($cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'/README');
    create_install($cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'/INSTALL');
    
    copy('Makefile.PL', $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'/Makefile.PL');
    print 'cp ', 'Makefile.PL ', $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'/Makefile.PL', "\n";
    
    copy('dist.json', $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'/dist.json');
    print 'cp ', 'dist.json ', $cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'/dist.json', "\n";
    
    #tarball
    system('tar -czf '.$cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'.tar.gz '.$cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'});
    print 'tar -czf '.$cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}.'.tar.gz '.$cfg->{'config'}->{'name'}.'-'.$cfg->{'config'}->{'version'}, "\n";
}

sub copydir {
    my ($dir, $to, $re) = @_;
    
    if(!-e $to.'/'.$dir) {
        print 'mkdir ', $to.'/'.$dir, "\n";
        mkdir($to.'/'.$dir) || Carp::Croak("Could not make directory: $!");
    }

    my ($f) = File::Util->new();
    my @files = File::Find::Rule->file()->name($re)->relative()->in($dir);
    foreach my $file (@files) {
        if(!-e $to.'/'.$dir.'/'.$file) {
            print 'cp ', $dir.'/'.$file, ' ', $to.'/'.$dir.'/'.$file, "\n";
            copy($dir.'/'.$file, $to.'/'.$dir.'/'.$file) || Carp::croak("Could not copy file from ".$dir."/".$file." to ".$to."/".$dir."/".$file.": $!");
            next;
        }
        
        #file exists, now check its time
        if($f->last_modified($dir.'/'.$file) != $f->last_modified('build/'.$dir.'/'.$file)) {
            print 'cp ', $dir.'/'.$file, ' ', $to.'/'.$dir.'/'.$file, "\n";
            copy($dir.'/'.$file, $to.'/'.$dir.'/'.$file) || Carp::croak("Could not copy file from ".$dir."/".$file." to ".$to."/".$dir."/".$file.": $!");
        }
    }
}

sub compiledir {
    my ($dir, $re, $ext, $o) = @_;
    
    #TODO: check source time and only compile if modified
    
    my @comps = ();
    my @files = File::Find::Rule->file()->name($re)->in($dir);
    foreach my $file (@files) {
        $file =~ /(.+)\..+/;
        my $out = $1.$ext;
        print join(' ',($CC, $CFLAGS, ($ext eq '' ? '' : '-c'), $o, $file, '-o', $out)), "\n";
        system(join(' ',($CC, $CFLAGS, ($ext eq '' ? '' : '-c'), $o, $file, '-o', $out)));
        push(@comps, $out);
    }
    
    return @comps;
}

sub read_config {
    my $json = read_file('dist.json');
    return from_json($json);
}

sub create_authors {
    my ($path) = @_;
    my $cfg = read_config();
    open(my $OUT, '>', $path) || Carp::croak("Could not create authors file: $!");
    if(ref($cfg->{'config'}->{'author'}) eq 'ARRAY') {
        foreach my $author (@{$cfg->{'config'}->{'author'}}) {
            print $OUT $author, $\;
        }
    } else {
        print $OUT $cfg->{'config'}->{'author'};
    }
    close($OUT);
}

sub create_license {
    my ($path) = @_;
    my $cfg = read_config();
    open(my $OUT, '>', $path) || Carp::croak("Could not create license file: $!");
    if(!defined($cfg->{'config'}->{'license'})) {
        Carp::croak('Missing license');
    }
    if(!defined($cfg->{'config'}->{'copyright_holder'})) {
        Carp::croak('Missing copyright holder');
    }
    my @td = localtime();
    if($cfg->{'config'}->{'license'} eq 'MIT') {
        print $OUT "Copyright (c) ", ($td[5]+1900), ' ', $cfg->{'config'}->{'copyright_holder'}, "\n\n";
print $OUT <<END
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
END
    } elsif($cfg->{'config'}->{'license'} eq 'BSD') {
        print $OUT "Copyright (c) ", ($td[5]+1900), ' ', $cfg->{'config'}->{'copyright_holder'}, "\n";
print $OUT <<END
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the names of its contributors
      may be used to endorse or promote products derived from this software without
      specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.
END
    } elsif($cfg->{'config'}->{'license'} eq 'GPL') {
        Carp::croak('Not implemented');
    } elsif($cfg->{'config'}->{'license'} eq 'Artistic' || $cfg->{'config'}->{'license'} eq 'Perl') {
        Carp::croak('Not implemented');
    } else {
        Carp::croak('Unrecognized license type');
    }
    close($OUT);
}

sub create_readme {
    my ($path) = @_;
    open(my $OUT, '>', $path) || Carp::croak("Could not create readme file: $!");
    my $cfg = read_config();
    if(!defined($cfg->{'config'}->{'name'})) {
        Carp::croak('Distribution name not defined');
    }
    
    if(!defined($cfg->{'config'}->{'version'})) {
        Carp::croak('Version not defined');
    }
    
    if(!defined($cfg->{'config'}->{'abstract'})) {
        Carp::croak('Abstract not defined');
    }
    
    if(!defined($cfg->{'config'}->{'copyright_holder'})) {
        Carp::croak('Missing copyright holder');
    }
    
    if(!defined($cfg->{'config'}->{'license'})) {
        Carp::croak('Missing license');
    }
    my @td = localtime();
    print $OUT "This archive contains the distribution ".$cfg->{'config'}->{'name'}.", version ".$cfg->{'config'}->{'version'}.":\n\n";
    print $OUT "  ", $cfg->{'config'}->{'abstract'}, "\n\n";
    print $OUT "This software is Copyright (c) ", ($td[5]+1900), " by ", $cfg->{'config'}->{'copyright_holder'}, "\n\n";
    print $OUT "This is free software, licensed under:\n\n";
    print $OUT "  ";
    if($cfg->{'config'}->{'license'} eq 'MIT') {
        print $OUT "The MIT (X11) License\n\n";
    } elsif($cfg->{'config'}->{'license'} eq 'BSD') {
        print $OUT "The Simplified BSD License\n\n";
    } else {
        Carp::croak('Unsupported license type');
    }
    if(defined($cfg->{'config'}->{'repository'})) {
        print $OUT "The source code for this project can be obtained from:\n\n";
        print $OUT "  ", $cfg->{'config'}->{'repository'}, "\n\n";
    }
    close($OUT);
}

sub create_install {
    my ($path) = @_;
    open(my $OUT, '>', $path) || Carp::croak("Could not create install file: $!");
    print $OUT "To install, run:\n\n";
    print $OUT "(perl Makefile.PL) && (perl Makefile.PL test) && (sudo perl Makefile.PL install)\n";
    close($OUT);
}
