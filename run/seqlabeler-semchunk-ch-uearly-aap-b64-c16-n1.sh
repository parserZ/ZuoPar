#!/bin/bash
ROOT=`pwd`
TRAIN=${ROOT}/data/semchunk/ch/train.semchunk.crfsuite.txt
DEVEL=${ROOT}/data/semchunk/ch/devel.semchunk.crfsuite.txt
TEST=${ROOT}/data/semchunk/ch/test.semchunk.crfsuite.txt
CONSTRAIN=${ROOT}/data/semchunk/ch/trans

DEVEL_PROPS=${ROOT}/data/semchunk/ch/devel.answer.props
TEST_PROPS=${ROOT}/data/semchunk/ch/test.answer.props

SIG=`date '+%Y-%m-%d-%H%M%S'`-seqlabeler-semchunk-ch-uearly-aap-b64-c16-n1
WORKSPACE=${ROOT}/workspace/${SIG}

MODEL_DIR=${WORKSPACE}/model
OUTPUT_DIR=${WORKSPACE}/output
EXE_DIR=${WORKSPACE}/bin

mkdir -p ${MODEL_DIR}
mkdir -p ${OUTPUT_DIR}
mkdir -p ${EXE_DIR}

MODEL_PREFIX=${MODEL_DIR}/model

EXE=${EXE_DIR}/sequence_labeler.${SIG}
cp ${ROOT}/bin/sequence_labeler ${EXE}

rm ${MODEL_PREFIX}.*

for i in `seq 1 100`; do
    ${EXE} multi-learn \
        -m ${MODEL_PREFIX} \
        -n ${CONSTRAIN} \
        -t 12 \
        -r ${TRAIN}

    cp ${MODEL_PREFIX} ${MODEL_PREFIX}.${i}
    bzip2 ${MODEL_PREFIX}.${i}

    ${EXE} test \
        -m ${MODEL_PREFIX} \
        -n ${CONSTRAIN} \
        -i ${DEVEL} \
        -o ${OUTPUT_DIR}/devel.${i}

    ${EXE} test \
        -m ${MODEL_PREFIX} \
        -n ${CONSTRAIN} \
        -i ${TEST} \
        -o ${OUTPUT_DIR}/test.${i}

    TMP=/tmp/`date +%M%H%S | base64`
    ${ROOT}/scripts/semchunk/semchunk_to_props2.py ${OUTPUT_DIR}/devel.${i} > ${TMP}
    awk '{print $1}' ${DEVEL_PROPS} | paste -d "\t" - ${TMP} | sed 's/^\t$//g' > ${OUTPUT_DIR}/devel.${i}.props

    ${ROOT}/scripts/semchunk/semchunk_to_props2.py ${OUTPUT_DIR}/test.${i} > ${TMP}
    awk '{print $1}' ${TEST_PROPS} | paste -d "\t" - ${TMP} | sed 's/^\t$//g' > ${OUTPUT_DIR}/test.${i}.props
    rm ${TMP}

    ${ROOT}/scripts/semchunk/srl-eval.pl ${DEVEL_PROPS} ${OUTPUT_DIR}/devel.${i}.props
    ${ROOT}/scripts/semchunk/srl-eval.pl ${TEST_PROPS}  ${OUTPUT_DIR}/test.${i}.props
done