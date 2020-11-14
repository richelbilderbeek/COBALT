/* $Id: Location_constraint.cpp 459331 2015-02-17 21:53:17Z dicuccio $
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
 * Author:  J. Chen
 *
 * File Description:
 *   Evaluate if feature matches to CLocation_constraint
 *
 * Remark:
 *   This code was originally generated by application DATATOOL
 *   using the following specifications:
 *   'macro.asn'.
 */

// standard includes
#include <ncbi_pch.hpp>

// generated includes
#include <objects/macro/Location_constraint.hpp>
#include <objects/macro/Strand_constraint.hpp>
#include <objects/macro/Seqtype_constraint.hpp>
#include <objects/macro/Partial_constraint.hpp>
#include <objects/macro/Location_type_constraint.hpp>
#include <objects/macro/Location_pos_constraint.hpp>
#include <objects/seqloc/Seq_loc.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

// destructor
CLocation_constraint::~CLocation_constraint(void)
{
}

bool CLocation_constraint :: x_IsLocationConstraintEmpty() const
{
  if (GetStrand() != eStrand_constraint_any
          || GetSeq_type() != eSeqtype_constraint_any
          || GetPartial5() != ePartial_constraint_either
          || GetPartial3() != ePartial_constraint_either
          || GetLocation_type() != eLocation_type_constraint_any
          || (CanGetEnd5()
                && GetEnd5().Which() != CLocation_pos_constraint::e_not_set)
          || (CanGetEnd3()
                && GetEnd3().Which() != CLocation_pos_constraint::e_not_set)) {
    return false;
  }
  return true;
};

bool CLocation_constraint :: x_DoesStrandMatchConstraint(const CSeq_loc& loc) const
{
  if (loc.Which() == CSeq_loc::e_not_set) {
     return false;
  }
  if (GetStrand() == eStrand_constraint_any) {
     return true;
  }

  if (loc.GetStrand() == eNa_strand_minus) {
      if (GetStrand() == eStrand_constraint_minus) {
         return true;
      }
      else return false;
  }
  else {
     if (GetStrand() == eStrand_constraint_plus) {
       return true;
     }
     else return false;
  }
};

bool CLocation_constraint :: x_DoesBioseqMatchSequenceType(CConstRef <CBioseq> bioseq, const ESeqtype_constraint& seq_type) const
{
  if (seq_type == eSeqtype_constraint_any
        || (bioseq->IsNa() && seq_type == eSeqtype_constraint_nuc)
        || (bioseq->IsAa() && seq_type == eSeqtype_constraint_prot)) {
      return true;
  }
  else return false;
};

bool CLocation_constraint :: x_DoesLocationMatchPartialnessConstraint(const CSeq_loc& loc) const
{
  bool partial5 = loc.IsPartialStart(eExtreme_Biological);
  bool partial3 = loc.IsPartialStop(eExtreme_Biological);
  if ( (GetPartial5() == ePartial_constraint_partial && !partial5)
         || (GetPartial5() == ePartial_constraint_complete && partial5) 
         || (GetPartial3() == ePartial_constraint_partial && !partial3)
         || (GetPartial3() == ePartial_constraint_complete && partial3) ) {
       return false;
    }
    else return true;
};

bool CLocation_constraint :: x_DoesLocationMatchTypeConstraint(const CSeq_loc& seq_loc) const
{
  bool has_null = false;
  int  num_intervals = 0;

  if (GetLocation_type() == eLocation_type_constraint_any) {
      return true;
  }
  else
  {
    for (CSeq_loc_CI sl_ci(seq_loc); sl_ci; ++ sl_ci) {
       if (sl_ci.GetEmbeddingSeq_loc().Which() == CSeq_loc::e_Null) {
           has_null = true;
       }
       else if (!sl_ci.IsEmpty()) num_intervals ++;
    }

    if (GetLocation_type() == eLocation_type_constraint_single_interval)
    {
        if (num_intervals == 1) {
           return true;
        }
    }
    else if (GetLocation_type() == eLocation_type_constraint_joined) {
      if (num_intervals > 1 && !has_null) {
          return true;
      }
    }
    else if (GetLocation_type() == eLocation_type_constraint_ordered) {
       if (num_intervals > 1 && has_null) {
          return true;
       }
    }
  }
  return false;
};

bool CLocation_constraint :: x_DoesLocationMatchDistanceConstraint(CConstRef <CBioseq> bioseq, const CSeq_loc& loc) const
{
  if (!CanGetEnd5() && !CanGetEnd3()) {
      return true;
  }

  unsigned pos = loc.GetStop(eExtreme_Positional);
  int pos2;
  if (bioseq.NotEmpty()) {
     pos2 = (bioseq->IsSetLength() ?  bioseq->GetLength() : 0) - pos - 1;
  }

  if (loc.GetStrand() == eNa_strand_minus) {
    if (CanGetEnd5()) {
      if (bioseq.Empty()) {
          return false;
      }
      else {
        if (!GetEnd5().Match(pos2)) {
           return false;
        }
      }
    }
    if (CanGetEnd3()) {
        return GetEnd3().Match(pos);
    }
  }
  else
  {
    if (CanGetEnd5() && !GetEnd5().Match(pos)) {
        return false;
    }
    if (CanGetEnd3()) {
      if (bioseq.Empty()) {
         return false;
      }
      return GetEnd3().Match(pos2);
    }
  }
  return true;
};

bool CLocation_constraint :: Match(const CSeq_feat& feat, CConstRef <CSeq_feat> feat_to, CConstRef <CBioseq> feat_bioseq) const
{
  if (x_IsLocationConstraintEmpty()) {
     return true;
  }
 
  const CSeq_loc& feat_loc = feat.GetLocation();
  if (GetStrand() != eStrand_constraint_any) {
    if (feat_bioseq.Empty()) {
       return false;
    }
    else if (feat_bioseq->IsAa()) {
      if (feat_to.Empty()) {  // when feat is product, feat_to points to cds
         return false;
      }
      else if (!x_DoesStrandMatchConstraint (feat_to->GetLocation())) {
        return false;
      }
    }
    else if (!x_DoesStrandMatchConstraint (feat_loc)) {
        return false;
    }
  }

  if (!x_DoesBioseqMatchSequenceType(feat_bioseq, GetSeq_type())) {
     return false;
  }

  if (!x_DoesLocationMatchPartialnessConstraint (feat_loc)) {
     return false;
  }

  if (!x_DoesLocationMatchTypeConstraint (feat_loc)) {
     return false;
  }

  if (!x_DoesLocationMatchDistanceConstraint(feat_bioseq, feat_loc)) {
     return false;
  }

  return true;
};

END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

/* Original file checksum: lines: 57, chars: 1750, CRC32: b7e64033 */
