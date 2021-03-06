/* $Id: Entrez2_id_list.cpp 481294 2015-10-08 14:03:49Z grichenk $
 * ===========================================================================
 *
 *                            PUBLIC DOMAIN NOTICE
 *               National Center for Biotechnology Information
 *
 *  This software/database is a "United States Government Work" under the
 *  terms of the United States Copyright Act.  It was written as part of
 *  the author's official duties as a United States Government employee and
 *  thus cannot be copyrighted.  This software/database is freely available
 *  to the public for use. The National Library of Medicine and the U.S.
 *  Government have not placed any restriction on its use or reproduction.
 *
 *  Although all reasonable efforts have been taken to ensure the accuracy
 *  and reliability of the software and data, the NLM and the U.S.
 *  Government do not and cannot warrant the performance or results that
 *  may be obtained by using this software or data. The NLM and the U.S.
 *  Government disclaim all warranties, express or implied, including
 *  warranties of performance, merchantability or fitness for any particular
 *  purpose.
 *
 *  Please cite the author in any work or product based on this material.
 *
 * ===========================================================================
 *
 * Author:  .......
 *
 * File Description:
 *   .......
 *
 * Remark:
 *   This code was originally generated by application DATATOOL
 *   using specifications from the ASN data definition file
 *   'entrez2.asn'.
 */

// standard includes

// generated includes
#include <ncbi_pch.hpp>
#include <objects/entrez2/Entrez2_id_list.hpp>

#include <corelib/ncbi_safe_static.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

static const size_t kUidSize = 32; // bits
const size_t        CEntrez2_id_list::sm_UidSize = kUidSize / 8; // bytes
CSafeStatic<CEntrez2_id_list::TUids> s_EmptyList;

CEntrez2_id_list::TUidIterator CEntrez2_id_list::GetUidIterator()
{
    return TUidIterator(SetUids(), kUidSize);
}

CEntrez2_id_list::TConstUidIterator
CEntrez2_id_list::GetConstUidIterator() const
{
    if (CanGetUids()) {
        return TConstUidIterator(GetUids(), kUidSize);
    } else {
        return TConstUidIterator(s_EmptyList.Get(), kUidSize);
    }
}

// destructor
CEntrez2_id_list::~CEntrez2_id_list(void)
{
}


void CEntrez2_id_list::Resize(size_t size)
{
    SetUids().resize(sm_UidSize * size);
    SetNum(size);
}


void CEntrez2_id_list::AssignUids(const vector<TUid>& uids)
{
    Resize(uids.size());

    TUidIterator it = GetUidIterator();
    ITERATE (vector<TUid>, iter, uids) {
        *it++ = *iter;
    }
}


// append an item to the list
void push_back(int uid);


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

/* Original file checksum: lines: 61, chars: 1906, CRC32: 6647067f */
