export DEVICE=hydrogen
export VENDOR=xiaomi

UPDATE_PACKAGE=$1

if [ "x$UPDATE_PACKAGE" = "x" ]; then
    echo You must specify the update.zip as first argument
    exit
fi

OUT=../../../vendor/$VENDOR/$DEVICE/proprietary
rm -rf $OUT/*

for FILE in `egrep -v '(^#|^$)' proprietary-files.txt`; do
  OLDIFS=$IFS IFS=":" PARSING_ARRAY=($FILE) IFS=$OLDIFS
      FILE=`echo ${PARSING_ARRAY[0]} | sed -e "s/^-//g"`
      DEST=${PARSING_ARRAY[1]}
      if [ -z $DEST ]
      then
        DEST=$FILE
      fi
      DIR=`dirname $DEST`
      if [ ! -d $BASE/$DIR ]; then
        mkdir -p $BASE/$DIR
      fi
  if [ ! -d $OUT/$DIR ]; then
    mkdir -p $OUT/$DIR
  fi
  unzip -j -o ${UPDATE_PACKAGE} system/$FILE -d $OUT/$DIR
done


./setup-makefiles.sh
