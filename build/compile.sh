#!/bin/sh

echo "=== Compile script ==="
echo "Execute at: $(pwd)"
echo ""

#don`t touch it
usecmake=false
compile=false
execute=false
clearcli=false

exename="sfml"
how=0

while getopts ":hecmb" opt;
do
    case $opt in
        h )
            echo "Usage:"
            echo "  -h      Display help"
            echo "  -b      Use cmake"
            echo "  -m      Compile using make"
            echo "  -e      Just execute"
            echo "  -c      Clear console"
        ;;
        e )
            execute=true
            how=$(( $how + 1 ))
        ;;
        b )
            usecmake=true
            how=$(( $how + 1 ))
        ;;
        m )
            compile=true
            how=$(( $how + 1 ))
        ;;
        c )
            clearcli=true
            how=$(( $how + 1 ))
        ;;
        \? )
            echo "Invalid option -$opt" 1>&2
            exit 1
        ;;
    esac
done

#check for arguments
if [ $how = 0 ]; then
    echo "Script need arguments!!!"
    exit 1
fi

#execute cmake
if [ $usecmake = true ]; then
    echo "Runing cmake"
    cmake ..
fi

#execute make
if [ $compile = true ]; then
    echo "Runing make"
    make
fi

#exectute executable
if [ $execute = true ]; then
    echo "Runing executable"

    #clear console
    if [ $clearcli = true ]; then
        clear
    fi

    ./$exename
fi

