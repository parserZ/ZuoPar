#ifndef __ZUOPAR_UTILS_IO_INSTANCE_DEPENDENCY_H__
#define __ZUOPAR_UTILS_IO_INSTANCE_DEPENDENCY_H__

#include <iostream>
#include "types/segmentation.h"
#include "types/postag.h"
#include "types/dependency.h"
#include "engine/token_alphabet.h"

namespace ZuoPar {
namespace IO {

namespace eg = ZuoPar::Engine;

/**
 * Read one dependency instance from the input stream.
 *
 *  @param[in]  is                The input stream
 *  @param[out] output            The output dependency parse tree
 *  @param[in]  forms_alphabet    The alphabet for forms
 *  @param[in]  postags_alphabet  The alphabet for postags
 *  @param[in]  deprels_alphabet  The alphabet for dependency relation
 *  @param[in]  incremental       Use to specify if add new key entry to the
 *                                alphabet.
 */
void read_dependency_instance(std::istream& is,
    Dependency& output,
    eg::TokenAlphabet& forms_alphabet,
    eg::TokenAlphabet& postags_alphabet,
    eg::TokenAlphabet& deprels_alphabet,
    bool incremental = true);

/**
 * Write one dependency instance to the output stream.
 *
 *  @param[out] os                The output stream
 *  @param[in]  output            The instance.
 *  @param[in]  forms_alphabet    The alphabet for forms
 *  @param[in]  postags_alphabet  The alphabet for postags
 *  @param[in]  deprels_alphabet  The alphabet for dependency relation
 */
void write_dependency_instance(std::ostream& os,
    const Dependency& output,
    const eg::TokenAlphabet& forms_alphabet,
    const eg::TokenAlphabet& postags_alphabet,
    const eg::TokenAlphabet& deprels_alphabet);

} //  end for namespace io
} //  end for namespace zuopar

#endif  //  end for __ZUOPAR_UTILS_IO_INSTANCE_DEPENDENCY_H__
