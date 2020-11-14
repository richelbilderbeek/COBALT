/* $Id: Seq_inst.hpp 518949 2016-11-09 16:44:19Z ivanov $
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
 *   using specifications from the data definition file
 *   'seq.asn'.
 */

#ifndef OBJECTS_SEQ_SEQ_INST_HPP
#define OBJECTS_SEQ_SEQ_INST_HPP


// generated includes
#include <objects/seq/Seq_inst_.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

class NCBI_SEQ_EXPORT CSeq_inst : public CSeq_inst_Base
{
    typedef CSeq_inst_Base Tparent;
public:
    // constructor
    CSeq_inst(void);
    // destructor
    ~CSeq_inst(void);

    // check molecule type for nucleotide or protein
    static bool IsNa(EMol mol);
    static bool IsAa(EMol mol);

    bool IsNa(void) const;
    bool IsAa(void) const;

    // translate EMol to string
    static string GetMoleculeClass(EMol mol);

    bool ConvertDeltaToRaw();

private:
    // Prohibit copy constructor and assignment operator
    CSeq_inst(const CSeq_inst& value);
    CSeq_inst& operator=(const CSeq_inst& value);

};



/////////////////// CSeq_inst inline methods

// constructor
inline
CSeq_inst::CSeq_inst(void)
{
}


inline
bool CSeq_inst::IsNa(EMol mol)
{
    return (mol == eMol_dna  ||
            mol == eMol_rna  ||
            mol == eMol_na);
}


inline
bool CSeq_inst::IsAa(EMol mol)
{
    return (mol == eMol_aa);
}


inline
bool CSeq_inst::IsNa(void) const
{
    return IsNa(GetMol());
}


inline
bool CSeq_inst::IsAa(void) const
{
    return IsAa(GetMol());
}


/////////////////// end of CSeq_inst inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

#endif // OBJECTS_SEQ_SEQ_INST_HPP
/* Original file checksum: lines: 93, chars: 2363, CRC32: 8de74472 */
