/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is CBash code.
 *
 * The Initial Developer of the Original Code is
 * Waruddar.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#pragma once
#include "../../Common.h"
#include "../../GenericRecord.h"
#include "INFORecord.h"
namespace Sk
{

struct DIALPACKDATA {
	
    DIALPACKDATA(bool unknown, int dialogueTab, int subtypeId, int unused) {
        this->unknown = unknown;
        this->dialogueTab = dialogueTab;
        this->subtypeId = subtypeId;
        this->unused = unused;
    }
	DIALPACKDATA() { unknown = false; dialogueTab = 0; subtypeId = 0; unused = 0; }
	~DIALPACKDATA() {}

	
	bool unknown;
	uint8_t dialogueTab;
	uint8_t subtypeId;
	uint8_t unused;

	bool operator ==(const DIALPACKDATA &other) const {
		return (
			this->dialogueTab == other.dialogueTab &&
			this->subtypeId == other.subtypeId &&
			this->subtypeId == other.subtypeId &&
			this->unused == other.unused
			);
	}

	bool operator !=(const DIALPACKDATA &other) const
	{
		return !(*this == other);
	}
	
};

class DIALRecord : public TES5Record //Texture Set
    {

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Player dialogue.
		ReqSimpleFloatSubRecord<flt_0> PNAM;
		OptSimpleSubRecord<FORMID> BNAM; //Branch formid
		ReqSimpleSubRecord<FORMID> QNAM; //Quest formid
		ReqSubRecord<DIALPACKDATA> DATA;
		ReqSimpleSubRecord<uint32_t> SNAM; //Subtype
		ReqSimpleSubRecord<uint32_t> TIFC; //Topic info count

		std::vector<Record*> INFO;

        DIALRecord(unsigned char *_recData=NULL);
        DIALRecord(DIALRecord *srcRecord);
        ~DIALRecord();

		uint32_t  GetType();
		char *  GetStrType();

		bool   VisitFormIDs(FormIDOp &op);

		int32_t  ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk);
		int32_t  Unload();
		int32_t  WriteRecord(FileWriter &writer);
		char *GetEditorIDKey() { return EDID.value; }

        bool operator ==(const DIALRecord &other) const;
        bool operator !=(const DIALRecord &other) const;
        bool equals(Record *other);
    };
}