#!/usr/bin/env python

#
# =========================================================================
# This file is part of six.sicd-python
# =========================================================================
#
# (C) Copyright 2004 - 2016, MDA Information Systems LLC
#
# six.sicd-python is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this program; If not,
# see <http://www.gnu.org/licenses/>.
#

import os
import sys

from shutil import move
from subprocess import call

import utils

def moveToOutputDir(source, outdir):
    if not isinstance(source, basestring):
        for filename in source:
            moveToOutputDir(filename, outdir)
        return

    if source in os.listdir(outdir):
        os.remove(os.path.join(outdir, source))
         
    move(os.path.join(os.getcwd(), source), outdir)

def run():
    outdir = os.path.join(utils.findSixHome(), 'regression_files', 'six.sidd')
    if not os.path.isdir(outdir):
        os.makedirs(outdir)

    # Make siddLegend
    binDir = os.path.join(utils.installPath(), 'bin')
    legendNameBase = 'siddLegend'
    print 'Creating SIDDs with legends'

    call([utils.executableName(os.path.join(binDir, 'test_create_sidd_legend')),
          legendNameBase])

    moveToOutputDir(['{}_blocked.nitf'.format(legendNameBase),
                     '{}_unblocked.nitf'.format(legendNameBase)],
                    outdir)

    # Make the rest of SIDDs through test_create_sidd_from_mem
    argToOutput = {
        '--lut Color'        : 'siddWithColorLUT.nitf',
        '--lut Mono'         : 'siddWithMonoLUT.nitf',
        '--lut None'         : 'siddWithNoLUT.nitf',
        '--multipleImages'   : 'siddMultipleImages.nitf',
        '--multipleSegments' : 'siddMultipleSegments.nitf'
        }

    for arg in argToOutput.keys():
        print 'Creating file {}'.format(argToOutput[arg])
        if '--lut' in arg:
            call([utils.executableName(os.path.join(binDir,
                    'test_create_sidd_from_mem')), '--lut', arg.split(' ')[1],
                    argToOutput[arg]], stdout = open(os.devnull, 'w'))
        else:
            call([utils.executableName(os.path.join(binDir,
                    'test_create_sidd_from_mem')), arg, argToOutput[arg]],
                     stdout = open(os.devnull, 'w'))
            
    moveToOutputDir(argToOutput.values(), outdir)
    
