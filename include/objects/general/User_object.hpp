/* $Id: User_object.hpp 501123 2016-05-11 17:29:51Z bollin $
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
 *   'general.asn'.
 */

#ifndef OBJECTS_GENERAL_USER_OBJECT_HPP
#define OBJECTS_GENERAL_USER_OBJECT_HPP


// generated includes
#include <objects/general/User_object_.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

class NCBI_GENERAL_EXPORT CUser_object : public CUser_object_Base
{
    typedef CUser_object_Base Tparent;
public:
    /// constructor
    CUser_object(void);
    /// destructor
    ~CUser_object(void);

    /// how to interpret the value in the AddField() conversion functions below.
    enum EParseField {
        eParse_String,    ///< Add string even if all numbers
        eParse_Number     ///< Parse a real or integer number, otherwise string
    };

    /// add a data field to the user object that holds a given value
    CUser_object& AddField(const string& label, const string& value,
                           EParseField parse = eParse_String);
    CUser_object& AddField(const string& label, const char* value,
                           EParseField parse = eParse_String);
    CUser_object& AddField(const string& label, int           value);
    CUser_object& AddField(const string& label, Int8          value);
    CUser_object& AddField(const string& label, double        value);
    CUser_object& AddField(const string& label, bool          value);
#ifdef NCBI_STRICT_GI
    CUser_object& AddField(const string& label, TGi           value);
#endif

    CUser_object& AddField(const string& label, const vector<string>& value);
    CUser_object& AddField(const string& label, const vector<int>&    value);
    CUser_object& AddField(const string& label, const vector<double>& value);

    CUser_object& AddField(const string& label, CUser_object& value);
    CUser_object& AddField(const string& label,
                           const vector< CRef<CUser_object> >& value);
    CUser_object& AddField(const string& label,
                           const vector< CRef<CUser_field> >& value);

    /// Access a named field in this user object.  This is a little
    /// sneaky in that it interprets a delimiter for recursion.
    /// This version will throw an exception if the field
    /// doesn't exist.
    const CUser_field&     GetField(const string& str,
                                    const string& delim = ".",
                                    NStr::ECase use_case = NStr::eCase) const;
    CConstRef<CUser_field> GetFieldRef(const string& str,
                                       const string& delim = ".",
                                       NStr::ECase use_case = NStr::eCase) const;

    /// Access a named field in this user object.  This is a little
    /// sneaky in that it interprets a delimiter for recursion.  The
    /// 'obj_subtype' parameter is used to set the subtype of a 
    /// sub-object if a new sub-object needs to be created
    CUser_field&      SetField(const string& str,
                               const string& delim = ".",
                               const string& obj_subtype = kEmptyStr,
                               NStr::ECase use_case = NStr::eCase);
    CRef<CUser_field> SetFieldRef(const string& str,
                                  const string& delim = ".",
                                  const string& obj_subtype = kEmptyStr,
                                  NStr::ECase use_case = NStr::eCase);

    /// Verify that a named field exists
    bool HasField(const string& str,
                  const string& delim = ".",
                  NStr::ECase use_case = NStr::eCase) const;

    /// enum controlling what to return for a label
    /// this mirrors a request inside of feature::GetLabel()
    enum ELabelContent {
        eType,
        eContent,
        eBoth
    };

    /// Append a label to label.  The type defaults to content for
    /// backward compatibility
    void GetLabel(string* label, ELabelContent mode = eContent) const;

    ///
    /// enums for implicit typing of user objects
    ///

    /// general category
    enum ECategory {
        eCategory_Unknown = -1,
        eCategory_Experiment
    };

    /// sub-category experiment
    enum EExperiment {
        eExperiment_Unknown = -1,
        eExperiment_Sage
    };

    /// accessors: classify a given user object
    ECategory GetCategory(void) const;

    /// sub-category accessors:
    EExperiment GetExperimentType(void) const;
    const CUser_object& GetExperiment(void) const;

    /// format a user object as a given type.  This returns a user-object
    /// that is suitable for containing whatever specifics might be needed
    CUser_object& SetCategory(ECategory category);

    /// format a user object as a given type.  This returns a user-object
    /// that is suitable for containing whatever specifics might be needed
    CUser_object& SetExperiment(EExperiment category);

    /// Object Type
    enum EObjectType {
        eObjectType_Unknown = -1,
        eObjectType_DBLink,
        eObjectType_StructuredComment,
        eObjectType_OriginalId,
        eObjectType_Unverified,
        eObjectType_ValidationSuppression,
        eObjectType_Cleanup,
        eObjectType_AutodefOptions,
        eObjectType_FileTrack
    };

    EObjectType GetObjectType() const;
    void SetObjectType(EObjectType obj_type);

    // for Unverified User-objects: Can have Organism and/or Feature and/or Misassembled
    bool IsUnverifiedOrganism() const;
    void AddUnverifiedOrganism();
    void RemoveUnverifiedOrganism();
    bool IsUnverifiedFeature() const;
    void AddUnverifiedFeature();
    void RemoveUnverifiedFeature();
    bool IsUnverifiedMisassembled() const;
    void AddUnverifiedMisassembled();
    void RemoveUnverifiedMisassembled();

    void UpdateNcbiCleanup(int version);

    // Set FileTrack URL
    void SetFileTrackURL(const string& url);
    void SetFileTrackUploadId(const string& upload_id);

private:
    /// Prohibit copy constructor and assignment operator
    CUser_object(const CUser_object& value);
    CUser_object& operator=(const CUser_object& value);

    bool x_IsUnverifiedType(const string& val) const;
    bool x_IsUnverifiedType(const string& val, const CUser_field& field) const;
    void x_AddUnverifiedType(const string& val);
    void x_RemoveUnverifiedType(const string& val);
};



/////////////////// CUser_object inline methods

// constructor
inline
CUser_object::CUser_object(void)
{
}


/////////////////// end of CUser_object inline methods


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

#endif // OBJECTS_GENERAL_USER_OBJECT_HPP
