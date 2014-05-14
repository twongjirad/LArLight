#!/bin/bash

temp=make_rootmap.$$.temp

rootlibmap() {
 ROOTMAP=$1
 SOFILE=$2
 LINKDEF=$3
 shift 3
 DEPS=$*
 if [[ -e $SOFILE && -e $LINKDEF ]]; then
     rlibmap -f -o $ROOTMAP -l $SOFILE -d $DEPS -c $LINKDEF 2>> $temp
     rm -f $temp
 fi
}

######################################################
# OpticalDetector
rootlibmap libOpticalDetector.rootmap libOpticalDetector.so $USER_DEV_DIR/OpticalDetector/LinkDef.h \
    libRawData.so libUtility.so libAnalysis.so libDataFormat.so libBase.so
#    libRawData.so libOpticalDetectorData.so libUtility.so
