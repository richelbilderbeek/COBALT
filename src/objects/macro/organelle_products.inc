/*  $Id: organelle_products.inc 423489 2014-01-06 13:19:47Z bollin $
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
 * Author:  Jonathan Kans et al.
 *
 * File Description:
 *   Built-in copy of organelle_products.txt.
 *
 */

static const char* const s_Defaultorganelleproducts[] = {
    "Suspect-rule-set ::= {",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"cytochrome oxidase subunit\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"cytochrome c oxidase subunit\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"NADH dehydrogenase subunit\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"cytochrome b\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"ATP synthase F0\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"photosystem I\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"PsbA\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"PsbB\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"PsbT\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"PsbH\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"ribulose-1,5-bisphosphate carboxylase/oxygenase\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"maturase K\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"ATPase subunit 6\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"ATPase subunit 8\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } ,",
    "  {",
    "    find",
    "      string-constraint {",
    "        match-text \"matK\" ,",
    "        match-location contains ,",
    "        case-sensitive FALSE ,",
    "        ignore-space FALSE ,",
    "        ignore-punct FALSE ,",
    "        whole-word FALSE ,",
    "        not-present FALSE } ,",
    "    rule-type none } }"
};
