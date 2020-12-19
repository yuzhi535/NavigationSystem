#!/bin/sh
LD_LIBRARY_PATH=$PWD/:$PWD
echo "LD_LIBRARY_PATH=$LD_LIBRARY_PATH"
 
 
PATH=$PATH:$PWD/bin
echo "PATH=$PATH"
 
appname=`basename $0 | sed s,\.sh$,,`
 
dirname=`dirname $0`
tmp="${dirname#?}"
 
if [ "${dirname%$tmp}" != "/" ]; then
dirname=$PWD/$dirname
fi
LD_LIBRARY_PATH=$dirname:$LD_LIBRARY_PATH
echo "LD_LIBRARY_PATH=$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH
export PATH
export QT_QPA_PLATFORM_PLUGIN_PATH=$PWD/plugins
$dirname/$appname "$@"
