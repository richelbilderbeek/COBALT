/* $Id: Packed_seqint.cpp 256179 2011-03-02 18:19:45Z vasilche $
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
 *   'seqloc.asn'.
 */

// standard includes

// generated includes
#include <ncbi_pch.hpp>
#include <objects/seqloc/Packed_seqint.hpp>
#include <objects/seqloc/Seq_id.hpp>
#include <objects/seqloc/Seq_interval.hpp>
#include <corelib/ncbiutil.hpp>


// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

// constructor
CPacked_seqint::CPacked_seqint(TId& id, const TRanges& ivals, TStrand strand)
{
    ITERATE(TRanges, ival, ivals) {
        AddInterval(id, ival->GetFrom(), ival->GetTo(), strand);
    }
}


// destructor
CPacked_seqint::~CPacked_seqint(void)
{
}

// length calculator
TSeqPos CPacked_seqint::GetLength(void) const
{
    TSeqPos length = 0;
    ITERATE ( Tdata, i, Get() ) {
            length += (**i).GetLength();
    }
    return length;
}


const CSeq_interval* CPacked_seqint::GetStartInt(ESeqLocExtremes ext) const
{
    return ext == eExtreme_Positional && IsReverseStrand() ?
        Get().back() : Get().front();
}


const CSeq_interval* CPacked_seqint::GetStopInt(ESeqLocExtremes ext) const
{
    return ext == eExtreme_Positional && IsReverseStrand() ?
        Get().front() : Get().back();
}


CSeq_interval* CPacked_seqint::SetStartInt(ESeqLocExtremes ext)
{
    return ext == eExtreme_Positional && IsReverseStrand() ?
        Set().back() : Set().front();
}


CSeq_interval* CPacked_seqint::SetStopInt(ESeqLocExtremes ext)
{
    return ext == eExtreme_Positional && IsReverseStrand() ?
        Set().front() : Set().back();
}


bool CPacked_seqint::IsPartialStart(ESeqLocExtremes ext) const
{
    if ( Get().empty() ) {
        return false;
    }
    return GetStartInt(ext)->IsPartialStart(ext);
}


bool CPacked_seqint::IsPartialStop(ESeqLocExtremes ext) const
{
    if ( Get().empty() ) {
        return false;
    }
    return GetStopInt(ext)->IsPartialStop(ext);
}


void CPacked_seqint::SetPartialStart(bool val, ESeqLocExtremes ext)
{
    if ( !Get().empty() ) {
        SetStartInt(ext)->SetPartialStart(val, ext);
    }
}


void CPacked_seqint::SetPartialStop(bool val, ESeqLocExtremes ext)
{
    if ( !Get().empty() ) {
        SetStopInt(ext)->SetPartialStop(val, ext);
    }
}


bool CPacked_seqint::IsTruncatedStart(ESeqLocExtremes ext) const
{
    if ( Get().empty() ) {
        return false;
    }
    return GetStartInt(ext)->IsTruncatedStart(ext);
}


bool CPacked_seqint::IsTruncatedStop(ESeqLocExtremes ext) const
{
    if ( Get().empty() ) {
        return false;
    }
    return GetStopInt(ext)->IsTruncatedStop(ext);
}


void CPacked_seqint::SetTruncatedStart(bool val, ESeqLocExtremes ext)
{
    if (!Set().empty()) {
        SetStartInt(ext)->SetTruncatedStart(val, ext);
    }
}


void CPacked_seqint::SetTruncatedStop(bool val, ESeqLocExtremes ext)
{
    if (!Set().empty()) {
        SetStopInt(ext)->SetTruncatedStop(val, ext);
    }
}


bool CPacked_seqint::IsSetStrand(EIsSetStrand flag) const
{
    ITERATE(Tdata, i, Get()) {
        switch (flag) {
        case eIsSetStrand_Any:
            if ( (*i)->IsSetStrand() ) return true;
            break;
        case eIsSetStrand_All:
            if ( !(*i)->IsSetStrand() ) return false;
            break;
        }
    }
    return flag == eIsSetStrand_Any ? false : true;
}


ENa_strand CPacked_seqint::GetStrand(void) const
{
    ENa_strand strand = eNa_strand_unknown;
    bool strand_set = false;
    const CSeq_id* id = NULL;
    ITERATE(Tdata, i, Get()) {
        // check for multiple IDs
        if (id == NULL) {
            id = &((*i)->GetId());
        } else if (id->Compare((*i)->GetId()) != CSeq_id::e_YES) {
            return eNa_strand_other;
        }

        ENa_strand istrand = (*i)->IsSetStrand() ? (*i)->GetStrand() : eNa_strand_unknown;
        if (strand == eNa_strand_unknown  &&  istrand == eNa_strand_plus) {
            strand = istrand;
            strand_set = true;
        } else if (strand == eNa_strand_plus  &&  istrand == eNa_strand_unknown) {
            // treat unknown as plus - do nothing
        } else if (!strand_set) {
            strand = istrand;
            strand_set = true;
        } else if (istrand != strand) {
            return eNa_strand_other;
        }
    }
    return strand;
}


TSeqPos CPacked_seqint::GetStart(ESeqLocExtremes ext) const
{
    if (Get().empty()) {
        return kInvalidSeqPos;
    }
    return GetStartInt(ext)->GetStart(ext);
}


TSeqPos CPacked_seqint::GetStop(ESeqLocExtremes ext) const
{
    if (Get().empty()) {
        return kInvalidSeqPos;
    }
    return GetStopInt(ext)->GetStop(ext);
}


void CPacked_seqint::AddInterval(const CSeq_interval& ival)
{
    CRef<CSeq_interval> new_ival(new CSeq_interval);
    new_ival->Assign(ival);
    Set().push_back(new_ival);
}


void CPacked_seqint::AddInterval(const CSeq_id& id, TSeqPos from, TSeqPos to,
                                 ENa_strand strand)
{
    CSeq_interval ival;
    ival.SetFrom(from);
    ival.SetTo(to);
    ival.SetId().Assign(id);
    if (strand != eNa_strand_unknown) {
        ival.SetStrand(strand);
    }
    AddInterval(ival);
}


void CPacked_seqint::AddIntervals(const CPacked_seqint& ivals)
{
    AddIntervals(ivals.Get());
}


void CPacked_seqint::AddIntervals(const Tdata& ivals)
{
    copy(ivals.begin(), ivals.end(), back_inserter(Set()));
}


void CPacked_seqint::SetStrand(TStrand strand)
{
    NON_CONST_ITERATE (Tdata, it, Set()) {
        (*it)->SetStrand(strand);
    }
}


void CPacked_seqint::ResetStrand()
{
    NON_CONST_ITERATE (Tdata, it, Set()) {
        (*it)->ResetStrand();
    }
}


void CPacked_seqint::FlipStrand(void)
{
    NON_CONST_ITERATE (Tdata, it, Set()) {
        (*it)->FlipStrand();
    }
}


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE
