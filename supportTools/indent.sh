#!/bin/bash

## @file indent.sh
#
# @author  Martin Ubl
# @version 1.0
# @date    2019-10-06
# @brief   The KETCube project indentation helper script
#
# @note Requirements:
#    dox2unix, indent tools (present in standard Debian/Fedora packages list)
#
# @attention
#
#  <h2><center>&copy; Copyright (c) 2019 University of West Bohemia in Pilsen
#  All rights reserved.</center></h2>
#
#  Developed by:
#  The SmartCampus Team
#  Department of Technologies and Measurement
#  www.smartcampus.cz | www.zcu.cz
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the “Software”),
#  to deal with the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the Software
#  is furnished to do so, subject to the following conditions:
#
#     - Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimers.
#
#     - Redistributions in binary form must reproduce the above copyright notice,
#       this list of conditions and the following disclaimers in the documentation
#       and/or other materials provided with the distribution.
#
#     - Neither the names of The SmartCampus Team, Department of Technologies and Measurement
#       and Faculty of Electrical Engineering University of West Bohemia in Pilsen,
#       nor the names of its contributors may be used to endorse or promote products
#       derived from this Software without specific prior written permission.
#
#  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
#  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
#  PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE CONTRIBUTORS OR COPYRIGHT HOLDERS
#  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
#  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
#  OR THE USE OR OTHER DEALINGS WITH THE SOFTWARE.


#####################
## Config          ##
#####################

REQUIRED_TOOLS="dos2unix indent"
SUBDIRS="Drivers/KETCube/core Drivers/KETCube/modules KETCube/core KETCube/modules/sensing KETCube/modules/communication"
INDENT_CMD="indent -kr -nut"

#####################
## Script          ##
#####################

# verify the presence of required tools
for i in $REQUIRED_TOOLS; do
	which $i >/dev/null || (echo "ERROR: Tool $i is not installed, please, install it first" && exit 1)
done

DRY=0
PRINTDIFF=0

# parse first argument
if [ $# -ge 1 ]; then
	if [ $1 = "detect" ]; then
		DRY=1
	elif [ $1 = "showdiff" ]; then
		DRY=1
		PRINTDIFF=1
	else
		echo "ERROR: unknown parameter: $1"
		exit 2
	fi
fi

SUCCESS=1

# open and redirect a new output channel for conditional redirect
exec 3>/dev/null
# "showdiff" mode does not redirect to /dev/null
if [ $PRINTDIFF -eq 1 ]; then
	exec 3>&1
fi

# go through each subdirectory
for SUBDIR in $SUBDIRS; do

	# if the subdirectory does not exist, exit
	if [ ! -d $SUBDIR ]; then
		echo "ERROR: subdirectory $SUBDIR does not exist"
		exit 3
	fi

	# for each file in this filder, perform indenting according to rules
	for file in $( ls $SUBDIR ); do
		if [ $DRY -eq 1 ]; then
			# dry run: just verify, that the file is indented; optionally show differences between indented and non-indented version
			cat $SUBDIR/$file | dos2unix | $INDENT_CMD | diff $SUBDIR/$file - >&3 2>&3 || ( echo "INDENT: file $SUBDIR/$file is not indented according to given rules" && SUCCESS=0 )
		else
			# regular run: indent files and overwrite original ones; delete temporary "old" copy the indent tool makes
			dos2unix $SUBDIR/$file >/dev/null 2>&1
			$INDENT_CMD $SUBDIR/$file >/dev/null 2>&1
			rm $SUBDIR/$file~
		fi
	done
done

# if the script indicated an error, do not exit with status 0 (we need to be able to signalize error by using return code)
if [ $SUCCESS -ne 1 ]; then
	echo "ERROR: some errors detected, process failed"
	exit 3
fi

