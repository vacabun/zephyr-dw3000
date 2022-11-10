/*! ----------------------------------------------------------------------------
 * @file    example_info.h
 * @brief
 *
 * @attention
 *
 * Copyright 2013-2018(c) Decawave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 */

#include <assert.h>
#include "examples_defines.h"

example_ptr example_pointer;

void build_examples(void)
{
    unsigned char test_cnt=0;

#ifdef TEST_READING_DEV_ID
    extern int read_dev_id(void);
    example_pointer=read_dev_id;
    test_cnt++;
#endif

    //Check that only 1 test was enabled in test_selection.h file
    assert(test_cnt==1);

}

