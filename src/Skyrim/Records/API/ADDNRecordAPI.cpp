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
#include "../ADDNRecord.h"

namespace Sk {

	uint32_t ADDNRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
	{
		switch (FieldID)
		{
		case 0: //recType
			return GetType();
		case 1: //flags1
			return UINT32_FLAG_FIELD;
		case 2: //fid
			return FORMID_FIELD;
		case 3: //versionControl1
			switch (WhichAttribute)
			{
			case 0: //fieldType
				return UINT8_ARRAY_FIELD;
			case 1: //fieldSize
				return 4;
			default:
				return UNKNOWN_FIELD;
			}
			return UNKNOWN_FIELD;
		case 4: //eid
			return ISTRING_FIELD;
		case 5: //formVersion
			return UINT16_FIELD;
		case 6: //versionControl2
			switch (WhichAttribute)
			{
			case 0: //fieldType
				return UINT8_ARRAY_FIELD;
			case 1: //fieldSize
				return 2;
			default:
				return UNKNOWN_FIELD;
			}
			return UNKNOWN_FIELD;
		case 7: //boundX1
			return SINT16_FIELD;
		case 8: //boundY1
			return SINT16_FIELD;
		case 9: //boundZ1
			return SINT16_FIELD;
		case 10: //boundX2
			return SINT16_FIELD;
		case 11: //boundY2
			return SINT16_FIELD;
		case 12: //boundZ2
			return SINT16_FIELD;
		case 13: //modPath
			return ISTRING_FIELD;
		case 14: //modt_p
			switch (WhichAttribute)
			{
			case 0: //fieldType
				return UINT8_ARRAY_FIELD;
			case 1: //fieldSize
				return MODL.MODT.IsLoaded() ? MODL.MODT.GetSize() : 0;
			default:
				return UNKNOWN_FIELD;
			}
			return UNKNOWN_FIELD;
		case 15: //nodeIndex
			return SINT16_FIELD;
		case 16: //sound
			return FORMID_FIELD;
		case 17: //masterParticleSystemCap
			return SINT16_FIELD;
		case 18: //flags
			return UINT16_FLAG_FIELD;
		default:
			return UNKNOWN_FIELD;
		}
		return UNKNOWN_FIELD;
	}

	void * ADDNRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
	{
		switch (FieldID)
		{
		case 1: //flags1
			return &flags;
		case 2: //fid
			return &formID;
		case 3: //versionControl1
			*FieldValues = &flagsUnk;
			return NULL;
		case 4: //eid
			return EDID.value;
		case 5: //formVersion
			return &formVersion;
		case 6: //versionControl2
			*FieldValues = &versionControl2[0];
			return NULL;
		case 7: //boundX1
			return &OBND.value.x1;
		case 8: //boundY1
			return &OBND.value.y1;
		case 9: //boundZ1
			return &OBND.value.z1;
		case 10: //boundX2
			return &OBND.value.x2;
		case 11: //boundY2
			return &OBND.value.y2;
		case 12: //boundZ2
			return &OBND.value.z2;
		case 13: //modPath
			return MODL.MODL.IsLoaded() ? MODL.MODL.value : NULL;
		case 14: //modt_p
			return MODL.MODT.IsLoaded() ? MODL.MODT.value : NULL;
		case 15: //nodeIndex
			return &DATA.value;
		case 16: //sound
			return SNAM.IsLoaded() ? &SNAM.value : NULL;
		case 17: //masterParticleSystemCap
			return &DNAM->masterParticleSystemCap;
		case 18: //flags
			return &DNAM->flags;
		default:
			return NULL;
		}
		return NULL;
	}

	bool ADDNRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
	{
		switch (FieldID)
		{
		case 1: //flags1
			SetHeaderFlagMask(*(uint32_t *)FieldValue);
			break;
		case 3: //versionControl1
			if (ArraySize != 4)
				break;
			((UINT8ARRAY)&flagsUnk)[0] = ((UINT8ARRAY)FieldValue)[0];
			((UINT8ARRAY)&flagsUnk)[1] = ((UINT8ARRAY)FieldValue)[1];
			((UINT8ARRAY)&flagsUnk)[2] = ((UINT8ARRAY)FieldValue)[2];
			((UINT8ARRAY)&flagsUnk)[3] = ((UINT8ARRAY)FieldValue)[3];
			break;
		case 4: //eid
			EDID.Copy((char *)FieldValue);
			break;
		case 5: //formVersion
			formVersion = *(uint16_t *)FieldValue;
			break;
		case 6: //versionControl2
			if (ArraySize != 2)
				break;
			versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];
			versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];
			break;
		case 7: //boundX1
			OBND.value.x1 = *(int16_t *)FieldValue;
			break;
		case 8: //boundY1
			OBND.value.y1 = *(int16_t *)FieldValue;
			break;
		case 9: //boundZ1
			OBND.value.z1 = *(int16_t *)FieldValue;
			break;
		case 10: //boundX2
			OBND.value.x2 = *(int16_t *)FieldValue;
			break;
		case 11: //boundY2
			OBND.value.y2 = *(int16_t *)FieldValue;
			break;
		case 12: //boundZ2
			OBND.value.z2 = *(int16_t *)FieldValue;
			break;
		case 13: //modPath
			MODL.MODL.Load();
			MODL.MODL.Copy((char *)FieldValue);
			break;
		case 14: //modt_p
			MODL.MODT.Load();
			MODL.MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
			break;
		case 15: //nodeIndex
			DATA.value = *(int16_t *)FieldValue;
		case 16: //sound
			SNAM.value = *(FORMID *)FieldValue;
			return true;
		case 17: //masterParticleSystemCap
			DNAM->masterParticleSystemCap = *(int16_t *)FieldValue;
		case 18: //flags
			DNAM->flags = *(uint16_t *)FieldValue;
		default:
			break;
		}
		return false;
	}

	void ADDNRecord::DeleteField(FIELD_IDENTIFIERS)
	{
		GENOBND defaultOBND;
		ADDNDNAM defaultDNAM;

		switch (FieldID)
		{
		case 1: //flags1
			SetHeaderFlagMask(0);
			return;
		case 3: //versionControl1
			flagsUnk = 0;
			return;
		case 4: //eid
			EDID.Unload();
			return;
		case 5: //formVersion
			formVersion = 0;
			return;
		case 6: //versionControl2
			versionControl2[0] = 0;
			versionControl2[1] = 0;
			return;
		case 7: //boundX1
			OBND.value.x1 = defaultOBND.x1;
			return;
		case 8: //boundY1
			OBND.value.y1 = defaultOBND.y1;
			return;
		case 9: //boundZ1
			OBND.value.z1 = defaultOBND.z1;
			return;
		case 10: //boundX2
			OBND.value.x2 = defaultOBND.x2;
			return;
		case 11: //boundY2
			OBND.value.y2 = defaultOBND.y2;
			return;
		case 12: //boundZ2
			OBND.value.z2 = defaultOBND.z2;
			return;
		case 13: //modPath
			if (MODL.MODL.IsLoaded())
				MODL.MODL.Unload();
			return;
		case 14: //modt_p
			if (MODL.MODT.IsLoaded())
				MODL.MODT.Unload();
			return;
		case 15: //nodeIndex
			DATA.Unload();
			return;
		case 16: //sound
			SNAM.Unload();
			return;
		case 17: //masterParticleSystemCap
			DNAM->masterParticleSystemCap = defaultDNAM.masterParticleSystemCap;
			return;
		case 18: //flags
			DNAM->flags = defaultDNAM.flags;
			return;
		default:
			return;
		}
	}

} // namespace Sk
