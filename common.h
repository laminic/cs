/*
 * =====================================================================================
 *
 *       Filename:  common.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/31/2013 09:42:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __COMMON_H__
#define __COMMON_H__

#define G(str) str==NULL?NULL:g_locale_to_utf8(str, -1, NULL, NULL, NULL)
#define L(str) str==NULL?NULL:g_locale_from_utf8(str, -1, NULL, NULL, NULL)

#endif
