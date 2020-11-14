/* $Id: Gb_qual.cpp 523793 2017-01-05 20:55:42Z fukanchi $
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
 *   using the following specifications:
 *   'seqfeat.asn'.
 */

// standard includes
#include <ncbi_pch.hpp>

// generated includes
#include <objects/seqfeat/Gb_qual.hpp>

// other includes
#include <serial/enumvalues.hpp>
#include <serial/serialimpl.hpp>


// generated classes


BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

// destructor
CGb_qual::~CGb_qual(void)
{
}


static const char * valid_inf_categories [] = {
    "EXISTENCE",
    "COORDINATES",
    "DESCRIPTION"
};

static const char * valid_inf_prefixes [] = {
    "ab initio prediction",
    "nucleotide motif",
    "profile",
    "protein motif",
    "similar to AA sequence",
    "similar to DNA sequence",
    "similar to RNA sequence",
    "similar to RNA sequence, EST",
    "similar to RNA sequence, mRNA",
    "similar to RNA sequence, other RNA",
    "similar to sequence",
    "alignment"
};


void CGb_qual::ParseExperiment(const string& orig, string& category, string& experiment, string& doi)
{
    experiment = orig;
    category.clear();
    doi.clear();
    NStr::TruncateSpacesInPlace(experiment);

    for (unsigned int i = 0; i < ArraySize(valid_inf_categories); i++) {
        if (NStr::StartsWith (experiment, valid_inf_categories[i])) {
            category = valid_inf_categories[i];
            experiment = experiment.substr(category.length());
            NStr::TruncateSpacesInPlace(experiment);
            if (NStr::StartsWith(experiment, ":")) {
                experiment = experiment.substr(1);
            }
            NStr::TruncateSpacesInPlace(experiment);
            break;
        }
    }
    if (NStr::EndsWith(experiment, "]")) {
        size_t start_doi = NStr::Find(experiment, "[");

        if (start_doi != NPOS) {
            doi = experiment.substr(start_doi + 1);
            doi = doi.substr(0, doi.length() - 1);
            experiment = experiment.substr(0, start_doi);
        }
    }
}


string CGb_qual::BuildExperiment(const string& category, const string& experiment, const string& doi)
{
    string rval;
    if (!NStr::IsBlank(category)) {
        rval += category + ":";
    }
    rval += experiment;
    if (!NStr::IsBlank(doi)) {
        rval += "[" + doi + "]";
    }
    return rval;
}


bool CGb_qual::x_CleanupRptAndReplaceSeq(string& val)
{
    if (NStr::IsBlank(val)) {
        return false;
    }
    // do not clean if val contains non-sequence characters
    if (string::npos != val.find_first_not_of("ACGTUacgtu")) {
        return false;
    }
    string orig = val;
    NStr::ToLower(val);
    NStr::ReplaceInPlace(val, "u", "t");
    return !NStr::Equal(orig, val);
}


bool CGb_qual::CleanupRptUnitSeq(string& val)
{
    return x_CleanupRptAndReplaceSeq(val);
}


bool CGb_qual::CleanupReplace(string& val)
{
    return x_CleanupRptAndReplaceSeq(val);
}


// converts dashes to a pair of dots, unless dots are already present
// also makes no change if characters other than digits or dashes are found
bool CGb_qual::CleanupRptUnitRange(string& val)
{
    if (NStr::IsBlank(val)) {
        return false;
    }
    if (NStr::Find(val, ".") != NPOS) {
        return false;
    }
    if (NStr::Find(val, "-") == NPOS) {
        return false;
    }
    if (string::npos != val.find_first_not_of("0123456789-")) {
        return false;
    }
    NStr::ReplaceInPlace(val, "-", "..");
    return true;
}


const CGb_qual::TLegalRepeatTypeSet &
CGb_qual::GetSetOfLegalRepeatTypes(void)
{
    static const char * repeat_types[] = {
        "centromeric_repeat",
        "direct",
        "dispersed",
        "engineered_foreign_repetitive_element",
        "flanking",
        "inverted",
        "long_terminal_repeat",
        "nested",
        "non_LTR_retrotransposon_polymeric_tract",
        "other",
        "tandem",
        "telomeric_repeat",
        "terminal",
        "X_element_combinatorial_repeat",
        "Y_prime_element"
    };


    DEFINE_STATIC_ARRAY_MAP_WITH_COPY(
        TLegalRepeatTypeSet, sc_LegalRepeatTypes, repeat_types);

    return sc_LegalRepeatTypes;
}


bool CGb_qual::IsValidRptTypeValue(const string& val)
{
    const TLegalRepeatTypeSet& repeat_types = GetSetOfLegalRepeatTypes();

    bool error = false;

    // look for list of values
    vector<string> rpt_types;
    NStr::Split(val, ",", rpt_types, NStr::fSplit_NoMergeDelims);
    ITERATE(vector<string>, it, rpt_types) {
        string v = (*it);
        NStr::TruncateSpacesInPlace(v);
        if (NStr::StartsWith(v, "(")) {
            v = v.substr(1);
        }
        if (NStr::EndsWith(v, ")")) {
            v = v.substr(0, v.length() - 1);
        }
        NStr::TruncateSpacesInPlace(v);
        if (repeat_types.find(v.c_str()) == repeat_types.end()) {
            error = true;
            break;
        }
    }

    return !error;
}


const CGb_qual::TLegalPseudogeneSet &
CGb_qual::GetSetOfLegalPseudogenes(void)
{
    static const char * pseudogenes[] = {
        "allelic",
        "processed",
        "unitary",
        "unknown",
        "unprocessed"
    };


    DEFINE_STATIC_ARRAY_MAP_WITH_COPY(
        TLegalPseudogeneSet, sc_LegalPseudogenes, pseudogenes);

    return sc_LegalPseudogenes;
}


bool CGb_qual::IsValidPseudogeneValue(const string& val)
{
    const TLegalPseudogeneSet& pseudogenes = GetSetOfLegalPseudogenes();

    if (pseudogenes.find(val.c_str()) == pseudogenes.end()) {
        return false;
    } else {
        return true;
    }
}


const CGb_qual::TLegalRecombinationClassSet &
CGb_qual::GetSetOfLegalRecombinationClassValues(void)
{
    static const char * misc_recombs[] = {
        "chromosome_breakpoint",
        "meiotic_recombination",
        "mitotic_recombination",
        "non_allelic_homologous_recombination"
    };


    DEFINE_STATIC_ARRAY_MAP_WITH_COPY(
        TLegalRecombinationClassSet, sc_LegalRecombinationClass, misc_recombs);

    return sc_LegalRecombinationClass;
}


// constructor
CInferencePrefixList::CInferencePrefixList(void)
{
}

//destructor
CInferencePrefixList::~CInferencePrefixList(void)
{
}


void CInferencePrefixList::GetPrefixAndRemainder (const string& inference, string& prefix, string& remainder)
{
    string category;
    prefix.clear();
    remainder.clear();
    string check = inference;

    for (unsigned int i = 0; i < ArraySize(valid_inf_categories); i++) {
        if (NStr::StartsWith (check, valid_inf_categories[i])) {
            category = valid_inf_categories[i];
            check = check.substr(category.length());
            NStr::TruncateSpacesInPlace(check);
            if (NStr::StartsWith(check, ":")) {
                check = check.substr(1);
            }
            if (NStr::StartsWith(check, " ")) {
                check = check.substr(1);
            }
            break;
        }
    }
    for (unsigned int i = 0; i < ArraySize(valid_inf_prefixes); i++) {
        if (NStr::StartsWith (check, valid_inf_prefixes[i], NStr::eNocase)) {
            prefix = valid_inf_prefixes[i];
        }
    }

    remainder = check.substr (prefix.length());
    NStr::TruncateSpacesInPlace (remainder);
}


static const char* s_LegalMobileElementStrings[] = {
    "transposon",
    "retrotransposon",
    "integron",
    "superintegron",
    "insertion sequence",
    "non-LTR retrotransposon",
    "P-element",
    "transposable element",
    "SINE",
    "MITE",
    "LINE",
    "other"
};


void CGb_qual::GetMobileElementValueElements(const string& val, string& element_type, string& element_name)
{
    element_type.clear();
    element_name.clear();
    for (size_t i = 0; i < ArraySize(s_LegalMobileElementStrings); ++i) {
        if (NStr::StartsWith(val, s_LegalMobileElementStrings[i], NStr::eNocase)) {
            element_name = val.substr(strlen(s_LegalMobileElementStrings[i]));
            if (!NStr::IsBlank(element_name) &&
                (!NStr::StartsWith(element_name, ":") || NStr::Equal(element_name, ":"))) {
                element_name.clear();
            } else {
                element_type = s_LegalMobileElementStrings[i];
            }
            break;
        }
    }
}


bool CGb_qual::IsLegalMobileElementValue(const string& val)
{
    string element_type;
    string element_name;
    GetMobileElementValueElements(val, element_type, element_name);
    if (NStr::IsBlank(element_type)) {
        return false;
    } else if (NStr::Equal(element_type, "other") && NStr::IsBlank(element_name)) {
        return false;
    } else {
        return true;
    }
}


static const char* s_IllegalQualNameStrings[] = {
    "anticodon",
    "citation",
    "codon_start",
    "db_xref",
    "evidence",
    "exception",
    "gene",
    "note",
    "protein_id",
    "pseudo",
    "transcript_id",
    "translation",
    "transl_except",
    "transl_table"
};

bool CGb_qual::IsIllegalQualName(const string& val)
{
    for (size_t i = 0;  i < ArraySize(s_IllegalQualNameStrings); ++i) {
        if (NStr::EqualNocase(val, s_IllegalQualNameStrings[i])) {
            return true;
        }
    }
    return false;
}

static string s_FindInArray(const string &val, const char **arr)
{
    string result;
    for (unsigned int i = 0; arr[i][0] != '\0'; i++) 
        if (arr[i] == val)
        {
            result = val;
            break;
        }
    return result;
}

static const char *kInferenceDBChoices[] = {
    "GenBank",
    "EMBL",
    "DDBJ",
    "INSD",
    "RefSeq",
    "UniProt",
    "Other",
    "\0" };

size_t kNumInferenceDBChoices = sizeof(kInferenceDBChoices) / sizeof(char *);

typedef SStaticPair<const char*, const char*>  TInferenceTypeSynonymPairElem;
static const TInferenceTypeSynonymPairElem k_inference_type_synonym_pair_map[] = {
    { "ab initio prediction", "ab initio prediction" },
    { "alignment", "alignment" },
    { "nucleotide motif", "nucleotide motif" },
    { "profile", "profile" },
    { "protein motif", "protein motif" },
    { "similar to AA", "similar to AA sequence" },
    { "similar to AA sequence", "similar to AA sequence" },
    { "similar to DNA", "similar to DNA sequence" },
    { "similar to DNA sequence", "similar to DNA sequence" },
    { "similar to EST", "similar to RNA sequence, EST" },
    { "similar to mRNA", "similar to RNA sequence, mRNA" },
    { "similar to RNA", "similar to RNA sequence" },
    { "similar to RNA sequence", "similar to RNA sequence" },
    { "similar to RNA sequence, EST", "similar to RNA sequence, EST" },
    { "similar to RNA sequence, mRNA", "similar to RNA sequence, mRNA" },
    { "similar to RNA sequence, other", "similar to RNA sequence, other" },
    { "similar to sequence", "similar to sequence" }
};


typedef CStaticArrayMap<const char*, const char*, PNocase_CStr> TInferenceTypeSynonymPairMap;
DEFINE_STATIC_ARRAY_MAP(TInferenceTypeSynonymPairMap, sc_InferenceTypeSynonymPairMap, k_inference_type_synonym_pair_map);


void CGb_qual::ParseInferenceString(string val, string &category, string &type_str, bool &is_same_species, string &database, 
                                    string &accession, string &program, string &version, string &acc_list)
{
    category.clear();
    static const char *categories[] = {"COORDINATES", "DESCRIPTION", "EXISTENCE", "\0"};
    for (unsigned int i = 0; categories[i][0] != '\0'; i++) 
    {
        if (NStr::StartsWith(val, categories[i], NStr::eNocase)) {
            category = categories[i];
            val = val.substr(strlen(categories[i]));
            NStr::TruncateSpacesInPlace(val);
            if (NStr::StartsWith(val, ":")) {
                val = val.substr(1);
                NStr::TruncateSpacesInPlace(val);
            }
            break;
        }
    }


    type_str.clear();
    is_same_species = false;
    TInferenceTypeSynonymPairMap::const_iterator match = sc_InferenceTypeSynonymPairMap.end();
    ITERATE(TInferenceTypeSynonymPairMap, it, sc_InferenceTypeSynonymPairMap) {
        if (strlen(it->first) > type_str.length() && NStr::StartsWith(val, it->first, NStr::eNocase)) {
            type_str = it->first;
            match = it;
        }
    }
    if (match != sc_InferenceTypeSynonymPairMap.end()) {
        type_str = match->second;
        val = val.substr(strlen(match->first));
        NStr::TruncateSpacesInPlace(val);
        if (NStr::StartsWith(val, "(same species)", NStr::eNocase)) {
            is_same_species = true;
            val = val.substr(14);
            NStr::TruncateSpacesInPlace(val);
        }
	    if (NStr::StartsWith(val, ":")) {
            val = val.substr(1);
            NStr::TruncateSpacesInPlace(val);
        }
    }

    // add type-dependent extra data
    if (NStr::StartsWith(type_str, "similar to ")) {

        NStr::TruncateSpacesInPlace(val);
        while (NStr::StartsWith(val, "|")) {
            val = val.substr(1);
            NStr::TruncateSpacesInPlace(val);
        }
        size_t pos = NStr::Find(val, ":");
        if (pos == NPOS) {
            database = s_FindInArray(val, kInferenceDBChoices);
            if (database.empty())
                accession = val;            
            else
                accession.clear();
        } else {
            string part1 = val.substr(0, pos);
            string part2 = val.substr(pos + 1);
            database = s_FindInArray(part1, kInferenceDBChoices);
            if (!database.empty())
            {
                accession = part2;            
            }
            else
            {
                if (NStr::IsBlank(part1)) 
                {
                    accession = part2;
                } else 
                {
                    accession = val;
                }
            }
        }
    } else if (NStr::EqualNocase(type_str, "profile") 
		         || NStr::EqualNocase(type_str, "nucleotide motif")
		         || NStr::EqualNocase(type_str, "protein motif")) {

        if (NStr::IsBlank (val)) {
            program.clear();
            version.clear();
        } else {
            size_t pos = NStr::Find(val, ":");
            if (pos == NPOS) {
                program = val;
                version.clear();
            } else {
                string part1 = val.substr(0, pos);
                string part2 = val.substr(pos + 1);
                program = part1;
                version = part2;
            }
        }
    } else if (NStr::EqualNocase(type_str, "ab initio prediction")) {

        if (NStr::IsBlank (val)) {
            program.clear();
            version.clear();
        } else {
            size_t pos = NStr::Find(val, ":");
            if (pos == NPOS) {
                program = val;
                version.clear();
            } else {
                string part1 = val.substr(0, pos);
                string part2 = val.substr(pos + 1);
                program = part1;
                version = part2;
            }
        }
    } else if (NStr::EqualNocase(type_str, "alignment")) {

        string acc_list_str;
        if (NStr::IsBlank (val)) {
            program.clear();
            version.clear();
        } else {
            size_t pos = NStr::Find(val, ":");
            if (pos == NPOS) {
                program = val;
                version.clear();
            } else {
                string part1 = val.substr(0, pos);
                string part2 = val.substr(pos + 1);
                program = part1;
                pos = NStr::Find(part2, ":");
                if (pos == NPOS) {
                    version = part2;
                    // set alignment list blank
                    acc_list.clear();
                } else {
                    string ver_str = part2.substr(0, pos);
                    acc_list_str = part2.substr(pos + 1);
                    version = ver_str;
                    // set alignment list
                    NStr::ReplaceInPlace(acc_list_str, ",", "\n");
                    acc_list = acc_list_str;
                }
            }
        }
    }
}

static void ReplaceIfNotFound(string &inference, const string &find, const string &replace)
{
    size_t start = 0;
    while (start != NPOS)
    {
        size_t pos1 = NStr::Find(inference, find, start);
        size_t pos2 = NStr::Find(inference, replace, start);
        if (pos1 == NPOS)
            break;
        if (pos1 != pos2)
            NStr::ReplaceInPlace(inference, find, replace, start, 1);
        start = pos1 + find.length();
    }
}

string CGb_qual::CleanupAndRepairInference( const string &orig_inference )
{
    string inference(orig_inference);
    if( inference.empty() ) {
        return inference;
    }

    string old_inf;
    while (old_inf != inference)
    {
        old_inf = inference;
        NStr::ReplaceInPlace(inference,"  ", " ");
        NStr::ReplaceInPlace(inference," :", ":");
        // NStr::ReplaceInPlace(inference,"::", ":");
        NStr::ReplaceInPlace(inference,":  ", ": ");
    }

    ReplaceIfNotFound(inference, "COORDINATES:", "COORDINATES: ");
    ReplaceIfNotFound(inference, "DESCRIPTION:", "DESCRIPTION: ");
    ReplaceIfNotFound(inference, "EXISTENCE:", "EXISTENCE: ");

    for (size_t i = 0; i < kNumInferenceDBChoices - 1; i++) {
        string find = kInferenceDBChoices[i];
        find += ": ";
        string replace = kInferenceDBChoices[i];
        replace += ":";
        NStr::ReplaceInPlace(inference, find, replace);
    }
    NStr::ReplaceInPlace(inference, "UniProtKB: ", "UniProtKB:");

    ITERATE(TInferenceTypeSynonymPairMap, it, sc_InferenceTypeSynonymPairMap) {
        string find = it->first;
        find += ": ";
        string replace = it->second;
        replace += ":";
        NStr::ReplaceInPlace(inference, find, replace);
    }
    for (size_t i = 0; i < ArraySize(valid_inf_prefixes); i++) {
        string find = valid_inf_prefixes[i];
        find += ": ";
        string replace = valid_inf_prefixes[i];
        replace += ":";
        NStr::ReplaceInPlace(inference, find, replace);
    }

    return inference;
}

END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

/* Original file checksum: lines: 65, chars: 1885, CRC32: 3224da35 */
