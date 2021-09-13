MY_DIR=`dirname $0`
LD_PRELOAD=${MY_DIR}/plugin/build/ExamplePlugin.dll LEAN_PATH=${MY_DIR}/build lean --plugin ${MY_DIR}/plugin/build/ExamplePlugin.dll "$@"
