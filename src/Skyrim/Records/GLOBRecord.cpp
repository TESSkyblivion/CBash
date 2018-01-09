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
#include "../../Common.h"
#include "../../ModFile.h"
#include "GLOBRecord.h"

namespace Sk
{
	GLOBRecord::GLOBRecord(unsigned char *_recData) :
		TES5Record(_recData)
	{
		//
	}

	GLOBRecord::GLOBRecord(GLOBRecord *srcRecord) :
		TES5Record()
	{
		if (srcRecord == NULL)
			return;

		flags = srcRecord->flags;
		formID = srcRecord->formID;
		flagsUnk = srcRecord->flagsUnk;
		formVersion = srcRecord->formVersion;
		versionControl2[0] = srcRecord->versionControl2[0];
		versionControl2[1] = srcRecord->versionControl2[1];

		recData = srcRecord->recData;
		if (!srcRecord->IsChanged())
			return;
		EDID = srcRecord->EDID;
		FNAM = srcRecord->FNAM;
		FLTV = srcRecord->FLTV;


		return;
	}

	GLOBRecord::~GLOBRecord()
	{
		//
	}

	uint32_t GLOBRecord::GetType()
	{
		return REV32(GLOB);
	}

	char * GLOBRecord::GetStrType()
	{
		return "GLOB";
	}


	bool GLOBRecord::VisitFormIDs(FormIDOp &op)
	{
		if (!IsLoaded())
			return false;

		return op.Stop();
	}


	int32_t GLOBRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
	{
		uint32_t subType = 0;
		uint32_t subSize = 0;
		StringLookups *LookupStrings = GetParentMod()->TES4.LookupStrings;
		while (buffer < end_buffer) {
			subType = *(uint32_t *)buffer;
			buffer += 4;
			switch (subType)
			{
			case REV32(XXXX):
				buffer += 2;
				subSize = *(uint32_t *)buffer;
				buffer += 4;
				subType = *(uint32_t *)buffer;
				buffer += 6;
				break;
			default:
				subSize = *(uint16_t *)buffer;
				buffer += 2;
				break;
			}
			switch (subType)
			{
			case REV32(EDID):
				EDID.Read(buffer, subSize, CompressedOnDisk);
				break;
			case REV32(FNAM):
				FNAM.Read(buffer, subSize);
				break;
			case REV32(FLTV):
				FLTV.Read(buffer, subSize);
				break;

			default:
				//printer("FileName = %s\n", FileName);
				printer("  GLOB: %08X - Unknown subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
				CBASH_CHUNK_DEBUG
					printer("  Size = %i\n", subSize);
				printer("  CurPos = %08x\n\n", buffer - 6);
				buffer = end_buffer;
				break;
			}
		};
		return 0;
	}

	int32_t GLOBRecord::Unload()
	{
		IsChanged(false);
		IsLoaded(false);
		EDID.Unload();
		FNAM.Unload();
		FLTV.Unload();

		return 1;
	}

	int32_t GLOBRecord::WriteRecord(FileWriter &writer)
	{
		WRITE(EDID);
		WRITE(FNAM);
		WRITE(FLTV);
		return -1;
	}

	bool GLOBRecord::operator ==(const GLOBRecord &other) const
	{
		return (EDID.equalsi(other.EDID) &&
			FNAM == other.FNAM &&
			FLTV == other.FLTV);
	}

	bool GLOBRecord::operator !=(const GLOBRecord &other) const
	{
		return !(*this == other);
	}

	bool GLOBRecord::equals(Record *other)
	{
		return *this == *(GLOBRecord *)other;
	}
}