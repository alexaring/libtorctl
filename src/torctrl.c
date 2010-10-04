/*
 * =====================================================================================
 *
 *       Filename:  torctl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/02/2010 07:42:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "socket.h"
#include "torctrl.h"
#include "stdio.h"

#define MAX_PW_LENGTH

static int check_str_err(char* str) {
	//Check on 250... 250 is OK command, otherwise there is an error.
	if (str[0] == '2' && str[1] == '5' && str[2]=='0') {
		return 0;
	}
	//TODO
	//DO error handling here...
	return -1;
}

int tctrl_authenticate(char* password) {
	int err;
	//Buffer to construct commit string
	char buf[128], *tmp;
	//Length for password, avoid bufferoverflow
	err = strlen(password);
	if (err>100) {
		return -1;
	}
	//Build cmd string
	sprintf(buf, "authenticate \"%s\"", password);
	err = send_request(buf);
	if (err<0) {
		return -1;
	}
	err = recv_request(&tmp);
	if (err<0) {
		return -1;
	}
	err = check_str_err(tmp);
	if (err<0) {
		return -1;
	}
	free(tmp);
	return 0;
}

static E_COUNTRY country_to_enum(char* country) {
	if (!strcmp(country, "af")) {
		return AF;
	}
	if (!strcmp(country, "ax")) {
		return AX;
	}
	if (!strcmp(country, "al")) {
		return AL;
	}
	if (!strcmp(country, "dz")) {
		return DZ;
	}
	if (!strcmp(country, "as")) {
		return AS;
	}
	if (!strcmp(country, "ad")) {
		return AD;
	}
	if (!strcmp(country, "ao")) {
		return AO;
	}
	if (!strcmp(country, "ai")) {
		return AI;
	}
	if (!strcmp(country, "aq")) {
		return AQ;
	}
	if (!strcmp(country, "ag")) {
		return AG;
	}
	if (!strcmp(country, "ar")) {
		return AR;
	}
	if (!strcmp(country, "am")) {
		return AM;
	}
	if (!strcmp(country, "aw")) {
		return AW;
	}
	if (!strcmp(country, "au")) {
		return AU;
	}
	if (!strcmp(country, "at")) {
		return AT;
	}
	if (!strcmp(country, "az")) {
		return AZ;
	}
	if (!strcmp(country, "bs")) {
		return BS;
	}
	if (!strcmp(country, "bh")) {
		return BH;
	}
	if (!strcmp(country, "bd")) {
		return BD;
	}
	if (!strcmp(country, "bb")) {
		return BB;
	}
	if (!strcmp(country, "by")) {
		return BY;
	}
	if (!strcmp(country, "be")) {
		return BE;
	}
	if (!strcmp(country, "bz")) {
		return BZ;
	}
	if (!strcmp(country, "bj")) {
		return BJ;
	}
	if (!strcmp(country, "bm")) {
		return BM;
	}
	if (!strcmp(country, "bt")) {
		return BT;
	}
	if (!strcmp(country, "bo")) {
		return BO;
	}
	if (!strcmp(country, "ba")) {
		return BA;
	}
	if (!strcmp(country, "bw")) {
		return BW;
	}
	if (!strcmp(country, "bv")) {
		return BV;
	}
	if (!strcmp(country, "br")) {
		return BR;
	}
	if (!strcmp(country, "io")) {
		return IO;
	}
	if (!strcmp(country, "bn")) {
		return BN;
	}
	if (!strcmp(country, "bg")) {
		return BG;
	}
	if (!strcmp(country, "bf")) {
		return BF;
	}
	if (!strcmp(country, "bi")) {
		return BI;
	}
	if (!strcmp(country, "kh")) {
		return KH;
	}
	if (!strcmp(country, "cm")) {
		return CM;
	}
	if (!strcmp(country, "ca")) {
		return CA;
	}
	if (!strcmp(country, "cv")) {
		return CV;
	}
	if (!strcmp(country, "ky")) {
		return KY;
	}
	if (!strcmp(country, "cf")) {
		return CF;
	}
	if (!strcmp(country, "td")) {
		return TD;
	}
	if (!strcmp(country, "cl")) {
		return CL;
	}
	if (!strcmp(country, "cn")) {
		return CN;
	}
	if (!strcmp(country, "cx")) {
		return CX;
	}
	if (!strcmp(country, "cc")) {
		return CC;
	}
	if (!strcmp(country, "co")) {
		return CO;
	}
	if (!strcmp(country, "km")) {
		return KM;
	}
	if (!strcmp(country, "cg")) {
		return CG;
	}
	if (!strcmp(country, "cd")) {
		return CD;
	}
	if (!strcmp(country, "ck")) {
		return CK;
	}
	if (!strcmp(country, "cr")) {
		return CR;
	}
	if (!strcmp(country, "ci")) {
		return CI;
	}
	if (!strcmp(country, "hr")) {
		return HR;
	}
	if (!strcmp(country, "cu")) {
		return CU;
	}
	if (!strcmp(country, "cy")) {
		return CY;
	}
	if (!strcmp(country, "cz")) {
		return CZ;
	}
	if (!strcmp(country, "dk")) {
		return DK;
	}
	if (!strcmp(country, "dj")) {
		return DJ;
	}
	if (!strcmp(country, "dm")) {
		return DM;
	}
	if (!strcmp(country, "do")) {
		return DO;
	}
	if (!strcmp(country, "ec")) {
		return EC;
	}
	if (!strcmp(country, "eg")) {
		return EG;
	}
	if (!strcmp(country, "sv")) {
		return SV;
	}
	if (!strcmp(country, "gq")) {
		return GQ;
	}
	if (!strcmp(country, "er")) {
		return ER;
	}
	if (!strcmp(country, "ee")) {
		return EE;
	}
	if (!strcmp(country, "et")) {
		return ET;
	}
	if (!strcmp(country, "fk")) {
		return FK;
	}
	if (!strcmp(country, "fo")) {
		return FO;
	}
	if (!strcmp(country, "fj")) {
		return FJ;
	}
	if (!strcmp(country, "fi")) {
		return FI;
	}
	if (!strcmp(country, "fr")) {
		return FR;
	}
	if (!strcmp(country, "gf")) {
		return GF;
	}
	if (!strcmp(country, "pf")) {
		return PF;
	}
	if (!strcmp(country, "tf")) {
		return TF;
	}
	if (!strcmp(country, "ga")) {
		return GA;
	}
	if (!strcmp(country, "gm")) {
		return GM;
	}
	if (!strcmp(country, "ge")) {
		return GE;
	}
	if (!strcmp(country, "de")) {
		return DE;
	}
	if (!strcmp(country, "gh")) {
		return GH;
	}
	if (!strcmp(country, "gi")) {
		return GI;
	}
	if (!strcmp(country, "gr")) {
		return GR;
	}
	if (!strcmp(country, "gl")) {
		return GL;
	}
	if (!strcmp(country, "gd")) {
		return GD;
	}
	if (!strcmp(country, "gp")) {
		return GP;
	}
	if (!strcmp(country, "gu")) {
		return GU;
	}
	if (!strcmp(country, "gt")) {
		return GT;
	}
	if (!strcmp(country, "gg")) {
		return GG;
	}
	if (!strcmp(country, "gn")) {
		return GN;
	}
	if (!strcmp(country, "gw")) {
		return GW;
	}
	if (!strcmp(country, "gy")) {
		return GY;
	}
	if (!strcmp(country, "ht")) {
		return HT;
	}
	if (!strcmp(country, "hm")) {
		return HM;
	}
	if (!strcmp(country, "va")) {
		return VA;
	}
	if (!strcmp(country, "hn")) {
		return HN;
	}
	if (!strcmp(country, "hk")) {
		return HK;
	}
	if (!strcmp(country, "hu")) {
		return HU;
	}
	if (!strcmp(country, "is")) {
		return IS;
	}
	if (!strcmp(country, "in")) {
		return IN;
	}
	if (!strcmp(country, "id")) {
		return ID;
	}
	if (!strcmp(country, "ir")) {
		return IR;
	}
	if (!strcmp(country, "iq")) {
		return IQ;
	}
	if (!strcmp(country, "ie")) {
		return IE;
	}
	if (!strcmp(country, "im")) {
		return IM;
	}
	if (!strcmp(country, "il")) {
		return IL;
	}
	if (!strcmp(country, "it")) {
		return IT;
	}
	if (!strcmp(country, "jm")) {
		return JM;
	}
	if (!strcmp(country, "jp")) {
		return JP;
	}
	if (!strcmp(country, "je")) {
		return JE;
	}
	if (!strcmp(country, "jo")) {
		return JO;
	}
	if (!strcmp(country, "kz")) {
		return KZ;
	}
	if (!strcmp(country, "ke")) {
		return KE;
	}
	if (!strcmp(country, "ki")) {
		return KI;
	}
	if (!strcmp(country, "kp")) {
		return KP;
	}
	if (!strcmp(country, "kr")) {
		return KR;
	}
	if (!strcmp(country, "kw")) {
		return KW;
	}
	if (!strcmp(country, "kg")) {
		return KG;
	}
	if (!strcmp(country, "la")) {
		return LA;
	}
	if (!strcmp(country, "lv")) {
		return LV;
	}
	if (!strcmp(country, "lb")) {
		return LB;
	}
	if (!strcmp(country, "ls")) {
		return LS;
	}
	if (!strcmp(country, "lr")) {
		return LR;
	}
	if (!strcmp(country, "ly")) {
		return LY;
	}
	if (!strcmp(country, "li")) {
		return LI;
	}
	if (!strcmp(country, "lt")) {
		return LT;
	}
	if (!strcmp(country, "lu")) {
		return LU;
	}
	if (!strcmp(country, "mo")) {
		return MO;
	}
	if (!strcmp(country, "mk")) {
		return MK;
	}
	if (!strcmp(country, "mg")) {
		return MG;
	}
	if (!strcmp(country, "mw")) {
		return MW;
	}
	if (!strcmp(country, "my")) {
		return MY;
	}
	if (!strcmp(country, "mv")) {
		return MV;
	}
	if (!strcmp(country, "ml")) {
		return ML;
	}
	if (!strcmp(country, "mt")) {
		return MT;
	}
	if (!strcmp(country, "mh")) {
		return MH;
	}
	if (!strcmp(country, "mq")) {
		return MQ;
	}
	if (!strcmp(country, "mr")) {
		return MR;
	}
	if (!strcmp(country, "mu")) {
		return MU;
	}
	if (!strcmp(country, "yt")) {
		return YT;
	}
	if (!strcmp(country, "mx")) {
		return MX;
	}
	if (!strcmp(country, "fm")) {
		return FM;
	}
	if (!strcmp(country, "md")) {
		return MD;
	}
	if (!strcmp(country, "mc")) {
		return MC;
	}
	if (!strcmp(country, "mn")) {
		return MN;
	}
	if (!strcmp(country, "me")) {
		return ME;
	}
	if (!strcmp(country, "ms")) {
		return MS;
	}
	if (!strcmp(country, "ma")) {
		return MA;
	}
	if (!strcmp(country, "mz")) {
		return MZ;
	}
	if (!strcmp(country, "mm")) {
		return MM;
	}
	if (!strcmp(country, "na")) {
		return NA;
	}
	if (!strcmp(country, "nr")) {
		return NR;
	}
	if (!strcmp(country, "np")) {
		return NP;
	}
	if (!strcmp(country, "nl")) {
		return NL;
	}
	if (!strcmp(country, "an")) {
		return AN;
	}
	if (!strcmp(country, "nc")) {
		return NC;
	}
	if (!strcmp(country, "nz")) {
		return NZ;
	}
	if (!strcmp(country, "ni")) {
		return NI;
	}
	if (!strcmp(country, "ne")) {
		return NE;
	}
	if (!strcmp(country, "ng")) {
		return NG;
	}
	if (!strcmp(country, "nu")) {
		return NU;
	}
	if (!strcmp(country, "nf")) {
		return NF;
	}
	if (!strcmp(country, "mp")) {
		return MP;
	}
	if (!strcmp(country, "no")) {
		return NO;
	}
	if (!strcmp(country, "om")) {
		return OM;
	}
	if (!strcmp(country, "pk")) {
		return PK;
	}
	if (!strcmp(country, "pw")) {
		return PW;
	}
	if (!strcmp(country, "ps")) {
		return PS;
	}
	if (!strcmp(country, "pa")) {
		return PA;
	}
	if (!strcmp(country, "pg")) {
		return PG;
	}
	if (!strcmp(country, "py")) {
		return PY;
	}
	if (!strcmp(country, "pe")) {
		return PE;
	}
	if (!strcmp(country, "ph")) {
		return PH;
	}
	if (!strcmp(country, "pn")) {
		return PN;
	}
	if (!strcmp(country, "pl")) {
		return PL;
	}
	if (!strcmp(country, "pt")) {
		return PT;
	}
	if (!strcmp(country, "pr")) {
		return PR;
	}
	if (!strcmp(country, "qa")) {
		return QA;
	}
	if (!strcmp(country, "re")) {
		return RE;
	}
	if (!strcmp(country, "ro")) {
		return RO;
	}
	if (!strcmp(country, "ru")) {
		return RU;
	}
	if (!strcmp(country, "rw")) {
		return RW;
	}
	if (!strcmp(country, "bl")) {
		return BL;
	}
	if (!strcmp(country, "sh")) {
		return SH;
	}
	if (!strcmp(country, "kn")) {
		return KN;
	}
	if (!strcmp(country, "lc")) {
		return LC;
	}
	if (!strcmp(country, "mf")) {
		return MF;
	}
	if (!strcmp(country, "pm")) {
		return PM;
	}
	if (!strcmp(country, "vc")) {
		return VC;
	}
	if (!strcmp(country, "ws")) {
		return WS;
	}
	if (!strcmp(country, "sm")) {
		return SM;
	}
	if (!strcmp(country, "st")) {
		return ST;
	}
	if (!strcmp(country, "sa")) {
		return SA;
	}
	if (!strcmp(country, "sn")) {
		return SN;
	}
	if (!strcmp(country, "rs")) {
		return RS;
	}
	if (!strcmp(country, "sc")) {
		return SC;
	}
	if (!strcmp(country, "sl")) {
		return SL;
	}
	if (!strcmp(country, "sg")) {
		return SG;
	}
	if (!strcmp(country, "sk")) {
		return SK;
	}
	if (!strcmp(country, "si")) {
		return SI;
	}
	if (!strcmp(country, "sb")) {
		return SB;
	}
	if (!strcmp(country, "so")) {
		return SO;
	}
	if (!strcmp(country, "za")) {
		return ZA;
	}
	if (!strcmp(country, "gs")) {
		return GS;
	}
	if (!strcmp(country, "es")) {
		return ES;
	}
	if (!strcmp(country, "lk")) {
		return LK;
	}
	if (!strcmp(country, "sd")) {
		return SD;
	}
	if (!strcmp(country, "sr")) {
		return SR;
	}
	if (!strcmp(country, "sj")) {
		return SJ;
	}
	if (!strcmp(country, "sz")) {
		return SZ;
	}
	if (!strcmp(country, "se")) {
		return SE;
	}
	if (!strcmp(country, "ch")) {
		return CH;
	}
	if (!strcmp(country, "sy")) {
		return SY;
	}
	if (!strcmp(country, "tw")) {
		return TW;
	}
	if (!strcmp(country, "tj")) {
		return TJ;
	}
	if (!strcmp(country, "tz")) {
		return TZ;
	}
	if (!strcmp(country, "th")) {
		return TH;
	}
	if (!strcmp(country, "tl")) {
		return TL;
	}
	if (!strcmp(country, "tg")) {
		return TG;
	}
	if (!strcmp(country, "tk")) {
		return TK;
	}
	if (!strcmp(country, "to")) {
		return TO;
	}
	if (!strcmp(country, "tt")) {
		return TT;
	}
	if (!strcmp(country, "tn")) {
		return TN;
	}
	if (!strcmp(country, "tr")) {
		return TR;
	}
	if (!strcmp(country, "tm")) {
		return TM;
	}
	if (!strcmp(country, "tc")) {
		return TC;
	}
	if (!strcmp(country, "tv")) {
		return TV;
	}
	if (!strcmp(country, "ug")) {
		return UG;
	}
	if (!strcmp(country, "ua")) {
		return UA;
	}
	if (!strcmp(country, "ae")) {
		return AE;
	}
	if (!strcmp(country, "gb")) {
		return GB;
	}
	if (!strcmp(country, "us")) {
		return US;
	}
	if (!strcmp(country, "um")) {
		return UM;
	}
	if (!strcmp(country, "uy")) {
		return UY;
	}
	if (!strcmp(country, "uz")) {
		return UZ;
	}
	if (!strcmp(country, "vu")) {
		return VU;
	}
	if (!strcmp(country, "ve")) {
		return VE;
	}
	if (!strcmp(country, "vn")) {
		return VN;
	}
	if (!strcmp(country, "vg")) {
		return VG;
	}
	if (!strcmp(country, "vi")) {
		return VI;
	}
	if (!strcmp(country, "wf")) {
		return WF;
	}
	if (!strcmp(country, "eh")) {
		return EH;
	}
	if (!strcmp(country, "ye")) {
		return YE;
	}
	if (!strcmp(country, "zm")) {
		return ZM;
	}
	if (!strcmp(country, "zw")) {
		return ZW;
	}
	return UNKNOWN;
}

E_COUNTRY tctrl_ip_to_country(char* ip) {
	int err;
	//Buffer to construct commit string
	char country[2];
	char buf[128], *tmp, *tmp2;
	err = strlen(ip);
	if (err>100) {
		return COUNTRY_ERROR;
	}
	sprintf(buf, "getinfo ip-to-country/%s", ip);
	err = send_request(buf);
	if (err<0) {
		return COUNTRY_ERROR;
	}
	err = recv_request(&tmp);
	if (err<0) {
		free(tmp);
		return COUNTRY_ERROR;
	}
	err = check_str_err(tmp);
	if (err<0) {
		free(tmp);
		return COUNTRY_ERROR;
	}
	//man rindex
	tmp2 = rindex(tmp, '=')+1;
	strncpy(country, tmp2, 2);
	//SWITCH CASE COUNTRY
	printf("%s\n", country);
	free(tmp);
	return country_to_enum(country);
}

int main(int argc, char* argv[]) {
	char* resstr;
	E_COUNTRY c;
	resstr = NULL;
	open_socket();
	tctrl_authenticate("torika");
	c = tctrl_ip_to_country("98.236.50.49");
	if ( c == US ) {
		printf("%s\n", "HURRA DE");
	}
	close_socket();
	return 0;
}

