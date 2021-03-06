#pragma once

#include <array>
#include <cstdint>

namespace ls_sec {
struct KeyMaterial {
  std::array<uint32_t, 18> header;
  std::array<std::array<uint32_t, 256>, 4> data;
};

static constexpr std::array<uint64_t, 8> kSeed = {{
    0x52D53304E4664070,
    0x7BE4F715AC8F4BED,
    0xFCA15E8B111F4724,
    0x417F8C2B310C9605,
    0xF3B1A8EBC188A5FD,
    0x50D5D31B56601699,
    0x308AE2A97F6832CD,
    0xF4EBC7DE34E88F2A,
}};

static constexpr KeyMaterial kKeyMaterial1 = KeyMaterial{
    .header = {{
        0xE813EC15,
        0xAE5B6CEA,
        0x6CA89E35,
        0x4CF05207,
        0x4806AD72,
        0xD5FDB061,
        0xC7FD55E4,
        0x46B160BE,
        0x82AB1888,
        0x6F1C061F,
        0xB9ED5302,
        0x05391939,
        0x93D86FFC,
        0x9C8B78FE,
        0xC51FF235,
        0x8CEE7883,
        0x96EA497E,
        0x7C3F81CA,
    }},
    .data = {{
        {{
            0x349A3164, 0x85CABA9F, 0x0925C3EC, 0x4DFC20DB, 0x66BCF8C7,
            0xC49CFFF2, 0x23F8A60A, 0x1836ED57, 0x5319D2D8, 0x6A3E2B3C,
            0xB1750EA3, 0x5E90F08B, 0x79AF2149, 0x4DB554BA, 0x2F693364,
            0x0F3E79DB, 0xFBDBDA72, 0x8C5E1023, 0x9B8A1D2A, 0xA08D493B,
            0x60ECC378, 0x3EDB5E91, 0xE63AD392, 0x4763C490, 0x699D4F35,
            0x3A4C6B8C, 0xECEEDF98, 0x921874A2, 0x2C3B75F0, 0xC8A94DD8,
            0x9AEACD32, 0x4CD1473F, 0xFF5DD017, 0x1355CCFB, 0xA4DF6FAC,
            0xD6946E66, 0x93DEB1F7, 0x5BA1A1E6, 0xAF8D3210, 0xF58339AF,
            0x19C9137B, 0x45AB1745, 0x027BE2C3, 0x0FEBD204, 0xEF573E02,
            0x82FBA559, 0x966D9750, 0xC75F6E48, 0x5D117A62, 0x0DA8401E,
            0x555E573E, 0xFCD4CEBD, 0x6EEE9752, 0x2E416589, 0x8F4E5731,
            0x226EF4A5, 0xF113DF59, 0x182DC602, 0x6CAC7390, 0x3CD7186C,
            0x0A9C5C36, 0x1262446E, 0xF73E2142, 0xA6CDE914, 0xFF8835F0,
            0xDE28B148, 0xF4D97681, 0xC47B135B, 0x6C94445E, 0x74699309,
            0xF5180902, 0x5C3DCF47, 0x6826ED46, 0x98F618A2, 0x5882D78A,
            0x6B9EA708, 0xA5FB9553, 0xC7848225, 0x634FAD1B, 0x573D14BF,
            0x9CAECDB5, 0xC63D0AF5, 0x9E9AC886, 0xA9605A3A, 0xB2B96D6F,
            0x84B6D2EA, 0x25D1E734, 0xBF097443, 0xA633DB5E, 0xE75E356F,
            0x184CDAEF, 0x2880982A, 0xF8F54F27, 0xAAEEB8D9, 0xB7571672,
            0x431D70BC, 0xCDF825F1, 0xAB4D334C, 0x1F107369, 0x33FE0685,
            0xCC51AA54, 0x4AF76E6F, 0xFAA6984B, 0xC39E8EA3, 0x5823E67A,
            0x63EE6300, 0x10AC0464, 0xE384D9EE, 0x3D27D4FD, 0x7441B6E6,
            0x29C815B5, 0x55732B19, 0x1103C32D, 0x82821CBE, 0xFAA06A0A,
            0xA6CFAD30, 0xF97AC0B0, 0x1197DA41, 0x1AC332A5, 0xD7777520,
            0xB78C649B, 0xA5F76B4E, 0xDE7E8F98, 0xF410FBB0, 0x08BF0F01,
            0xEC880D6F, 0x8AC457D6, 0x5911D66C, 0xEC091705, 0xB43A07E7,
            0xDB463B42, 0x7D79D6F1, 0x7753FB09, 0x358D77FA, 0x430E4767,
            0x41E32293, 0x1505050A, 0x13B599A9, 0xD12FF07D, 0x4DE5E72A,
            0x1B6BABEE, 0xC3E58FB5, 0x8CD9FFCE, 0x3A031286, 0xC9ED35C3,
            0x61D54C65, 0xEC538477, 0x8A0B44FD, 0x85C12CDE, 0x9C1649D9,
            0x34226DEE, 0x074C363D, 0xDA45157C, 0xD90BD7C0, 0x3EF8FF7A,
            0xE4769568, 0xA7E35774, 0x5D62F204, 0x3EA9CBBC, 0x84B88FA6,
            0x3B0E0457, 0x75DBC341, 0xE91406B1, 0x85B76900, 0xF447FE6A,
            0x1D12ABB2, 0xC73DE105, 0x71B4BC02, 0xBA37BD26, 0x8D3B3C00,
            0x3328905B, 0xB39BDFBB, 0xDEBFE7A9, 0x5CA2DB5F, 0x7713B03C,
            0xA1D96145, 0xB013F0A8, 0xE026DCF5, 0x98BB36A3, 0xAFC61518,
            0x881B1096, 0xF2EEEEAD, 0x2BE4CC7D, 0x9122D501, 0x6612270D,
            0x04FEBE6E, 0x8ED69D68, 0x0250B014, 0xACA682BB, 0x45ACDC97,
            0xD82CEAFC, 0x48E1F4AB, 0xAD6CE580, 0x05E906D8, 0x9E1A160A,
            0x06608F9D, 0x7F35342C, 0xC0EB0EB5, 0x03C3A792, 0xBA2E19DB,
            0xEAA3D476, 0xAA9E8BF7, 0x79C3A3CF, 0xFD51D0BC, 0xB2FE6A84,
            0x371703A2, 0x7D098D09, 0x7E5B556A, 0x0D1F18C0, 0x44D6C102,
            0xD451F8AD, 0x593BA6AC, 0xF9F0F691, 0x09780793, 0x71DB07D8,
            0x00EB65EA, 0x1445FC15, 0xC9D8A601, 0x96050CF1, 0xA4F5B71C,
            0xDCD4EE03, 0x8E61BB7C, 0x851E700A, 0x21E918E3, 0x13E21F51,
            0x7719484D, 0x0FA4DB14, 0xDB70EBCD, 0x54B14C0C, 0x1F0C3A3E,
            0xAF90B083, 0x74FF445D, 0xA7D0A611, 0x687F8285, 0xC403DC1C,
            0x98B8FC11, 0x9D13DFE2, 0xF27CDD7C, 0x8334CF1D, 0xC38D7398,
            0x56D87A93, 0x6EE70D0D, 0x650FAC36, 0xD4529EB0, 0xCA81379E,
            0x04155F31, 0x806E4DAB, 0xFBEC7589, 0x61160A64, 0x4A1E0FEC,
            0xEED49950, 0x3E14B39E, 0x7974438A, 0xF265621A, 0xD0736E87,
            0x980DC594,
        }},
        {{
            0xEF0172FE, 0xACF1C9ED, 0x7825B08E, 0x94FFA2F2, 0xC9289426,
            0xD5644FE7, 0x28A399D9, 0xB62E783F, 0xE302F037, 0xF373F9F4,
            0x7B36B756, 0xBC2CF053, 0x3AA190DB, 0xC86EF2AD, 0xC58F48BF,
            0x94C3737B, 0xDBB4581E, 0x0325063E, 0x528AE3BC, 0x9F3E8E41,
            0x40A352F0, 0xBB7B4CDE, 0x51B55266, 0x854279F5, 0xAEF100A4,
            0x165BC082, 0x950F255D, 0x03D5B31A, 0x2387DE20, 0x5A8C182F,
            0x34A6C854, 0x91C44DC0, 0xA2D4834D, 0x0348376E, 0xB01EA24E,
            0x21C23C8F, 0xF2A4E82F, 0x04A2FABF, 0x8431B727, 0xEC4D9B29,
            0xA61BEDA8, 0x3DF73976, 0x1D3ED935, 0x4AD99648, 0x62F30DC0,
            0x5EB2B7FC, 0xAAD2133B, 0x89320EA2, 0xA16FF8D7, 0xF03D9403,
            0x44D376E7, 0x6C5EEB26, 0x2F8B0FDA, 0xC4D9CD3B, 0x0F598252,
            0xE9D0E431, 0xB9487338, 0xC3575A00, 0x0444C21E, 0xA8684A8E,
            0xB7D32FFD, 0xD82E0476, 0x9E53D126, 0x686C68C3, 0x5AEE3695,
            0x297AC263, 0x0C7D8593, 0x73D0BBA0, 0xF45F6FD0, 0xD04BFE25,
            0x5A202CE3, 0x03C0CED5, 0x7E9932B8, 0x55FF6D39, 0xF8F659E9,
            0x93C8BCA3, 0x96A2EBA8, 0xE6C1E9AA, 0x62FF40CB, 0x646F808E,
            0x949404C2, 0xA56664C9, 0xB54F8CDB, 0x8CD633EE, 0xB5F1E7A9,
            0x3C9868FE, 0x85ECD3E6, 0x1D9C7A5E, 0x28D76CFD, 0x43DC2ECC,
            0xCA7C030A, 0x77015619, 0xA80E8C4A, 0x32223D76, 0x9A0B6E9F,
            0xF6C86142, 0x4F08A782, 0x9160F535, 0x5C181FC1, 0x0FF08632,
            0xD6F1E693, 0x3E91BCD0, 0xA8C192CD, 0xEB8BD294, 0x2E2C34DF,
            0xAD9270BC, 0xE7C11F13, 0x6B1B97B2, 0xDDF0916E, 0xC52EE357,
            0x9424B93B, 0x3F1B9C4E, 0x8A86281E, 0xCFFB5111, 0x992E4BE3,
            0x5FDE8E86, 0x429164C8, 0x5B91457D, 0x2D117B86, 0x4B206DF9,
            0x2BCA39C4, 0xF3C368DD, 0xFC503CDA, 0x17A43178, 0x477570F6,
            0x29469B54, 0x755D0C3C, 0x257D4BE7, 0x3E9726A7, 0xC5D37553,
            0x4BBEF76A, 0x73B093CD, 0x6C42388C, 0xB9B93F9A, 0x2B509077,
            0x157B5407, 0x316D8887, 0xC8A333F0, 0x26408830, 0x88406018,
            0x178C25D1, 0x5E2E6485, 0x17AE0C1A, 0x1D3056A6, 0x8A40A6EB,
            0xAEDF615E, 0x76C61F07, 0x61AFFF4B, 0xC8B19F84, 0xA8DD031D,
            0x32ED1E04, 0x650E7A54, 0x3F355046, 0x416154C1, 0x4B42F507,
            0x4F99E501, 0x97944470, 0xCFFF06CA, 0x2DE248DF, 0x36EA2F54,
            0x00B1315C, 0x5DB6E50B, 0xE57A5E82, 0x58E79671, 0xB096BB7E,
            0xD9468647, 0x9E8A408B, 0xFA2A736D, 0xAB5404C9, 0xC0C96E14,
            0x82655A1E, 0x822D97C5, 0xDD9C9E7F, 0x34CADCF6, 0xC0EFAC61,
            0xA2F3837C, 0x36C5BCF9, 0xE1934DD1, 0xB2BF8A31, 0x761738AE,
            0xE31D1DF2, 0x7AA84C10, 0xAE5E7F5E, 0x00A360A5, 0xC2A9D757,
            0x1AC28895, 0xB963F750, 0x88B58ED5, 0xD3C6D19E, 0x606CC514,
            0xD579A905, 0xAA28315B, 0x3A93F01A, 0x4D29F540, 0xC8F59A8D,
            0xE71957EA, 0x2D9F3769, 0xB6F415B5, 0x99C8882D, 0x504B0E36,
            0x2BF12F0B, 0xF90C2648, 0x061A385D, 0x1195DD23, 0x62B00207,
            0x2BCBF4F3, 0x70887523, 0x9F9E51B1, 0x9A212242, 0x928EF16A,
            0x9BE547CD, 0x716752F8, 0xD70D7E99, 0x8D4F14CD, 0x448A4AED,
            0x5BAEE03C, 0xEA8B8DE6, 0x5CC62978, 0xF84C10AD, 0x78E7D28F,
            0xE2D6EB3A, 0xBC05A25E, 0x7699FD62, 0x468A77A8, 0xFAEE0313,
            0x388C2572, 0x8728DEEC, 0xC2F7D131, 0x2F66BFBE, 0xC34EA214,
            0xEE452308, 0xE9144DA5, 0x2E1EB77F, 0x478B94DC, 0xA5250804,
            0x1063CFAB, 0x4A8F7F12, 0x5E354B01, 0x883D4B4B, 0x0B558639,
            0xF5513B36, 0x00C14278, 0xB46DE83A, 0x5859D16D, 0x249E95AA,
            0x959C2676, 0xBF54A4AC, 0xAF3B032B, 0x53C02913, 0x9BE1F5E6,
            0x16CA7628, 0xCE5290BB, 0xE1285AA4, 0x72B8751A, 0xFC1AC1CE,
            0x761BA2E8,
        }},
        {{
            0xEF84551F, 0x27979ACE, 0x80EC9A85, 0xC6BA7211, 0x27F67513,
            0xA647E047, 0xD6324AD2, 0x90A8FD9C, 0x9020980E, 0x3B622AE9,
            0x1894C4C2, 0x8744F86B, 0x9E81668F, 0x12A0C3FE, 0xB06CE63B,
            0x0A9AD70E, 0xF03726DA, 0x7C697704, 0x2BEC9A6A, 0xF23E3E81,
            0xCA9E6D20, 0x2AB584A2, 0x95F8906F, 0xEA569F3B, 0xE4B3ECA6,
            0x34F4F597, 0x53CC8E97, 0x61D5986C, 0xE820E355, 0x90BDEEF4,
            0x95346C71, 0x8ED352C3, 0xA50517F8, 0x841D4DC1, 0x93C4893D,
            0x60E56A4F, 0x0DBE1448, 0xC0C9BD0C, 0x5F70A73E, 0x816D2706,
            0xC1712CC1, 0x2129A7F2, 0x473887F3, 0xB049471A, 0x34E7E699,
            0x7568D07F, 0xA274B682, 0x43788AA5, 0xCEB15929, 0xD98A06A5,
            0xD252426E, 0x82338F82, 0xAEC1CBD9, 0xA17AF214, 0x7C3DFF3D,
            0x0080862C, 0xD688FFAE, 0xC1FA8A40, 0x146FB554, 0xAD0BBEEB,
            0xAEF8E4F4, 0x2B5D0E80, 0xF7F62436, 0xB11C30BF, 0x395C8FA9,
            0x65BCFD61, 0xCB1150DF, 0x33410334, 0x18B6880C, 0x23F545AE,
            0x825AF6C4, 0x62085128, 0x8F9B0692, 0x2D0589A5, 0x46DDCA1B,
            0x9B9A2B26, 0xA2B164C9, 0x3FE57A47, 0xA5859C3B, 0xFD1A3587,
            0x5D12C6C6, 0x1FD6DF72, 0xC01BAA53, 0x48B38489, 0x1AF0D528,
            0x653978CE, 0x66E651AD, 0x93E1431D, 0x4AC7E3DC, 0x3672F4ED,
            0x1B6B47B0, 0x52981A7B, 0xF9B23939, 0xA3D35A4B, 0x4B051CA8,
            0xD55F4988, 0xC90D551B, 0x55052644, 0xAA0E5892, 0x6E9466A2,
            0xC5271935, 0x5485D1BF, 0x32CC1BD0, 0xF8B27AE1, 0x54D58C98,
            0x0F0D4464, 0xD79561E4, 0x471D8C65, 0xA4B7D9C3, 0x7E02FBB1,
            0xA4F62CF1, 0xB319378B, 0x529AC147, 0xCDB9EC8C, 0xBB7C1977,
            0xA965D184, 0x5962299E, 0x8A424D4D, 0xF5E414B2, 0xA7EEDAD0,
            0x272A7A2E, 0xF5F79CF2, 0x7398ED00, 0x8EEA759B, 0x716F0D6A,
            0x2FA790C6, 0x8D37B3E2, 0x7476247B, 0x96D64840, 0xCB36F40B,
            0x86134CD5, 0x42ACC3CB, 0x54687DE9, 0x6F139188, 0xB8A7E69D,
            0x70D52CA8, 0x950B8903, 0x24F30040, 0xD9364A1F, 0x9A489C4D,
            0x4D2C6573, 0x36B0F1BD, 0xAC3E8D2F, 0xCBCA34AA, 0x89CC9E13,
            0xB57A9792, 0xF4B97EA6, 0x7F40CAFF, 0x41E06B8F, 0x01DC8CA7,
            0x7047835D, 0xCAF06E07, 0xCE3166ED, 0x461B02A6, 0x986FFD82,
            0x994339E5, 0xECCCE79D, 0xF8E94954, 0x81845AC1, 0x7041F2B3,
            0xAEF81D26, 0x80F66DF2, 0xEEB98066, 0xD7680496, 0xEB045D13,
            0xACD51786, 0xA6E88C37, 0xAC89550F, 0x4CB76F7F, 0xB2C39471,
            0xE7CFF429, 0x62BFF472, 0x2F48314B, 0x6909EFA4, 0x1601D60A,
            0xED86E1B1, 0x56BC6BED, 0x5E2E690B, 0x1BDCB81D, 0x9BA78896,
            0xD14493D9, 0xCCC812E8, 0x6A11C2F1, 0x8F82CC4F, 0x63C4DDB5,
            0x4604AF89, 0x1958DC1B, 0x0F45700D, 0x4A0162EE, 0x47963EF2,
            0xF822CEA7, 0x9E2781A5, 0xFABA2CB0, 0x336C1882, 0xCAFC34AF,
            0x11A91377, 0xF7EC9131, 0x9AD9DCFF, 0x9051CE01, 0x7E135E89,
            0xE36E5442, 0x1630D8A7, 0xF483609C, 0x26A71FF6, 0xB3257181,
            0x22EBA3B7, 0x2D5470E7, 0x5BBEB076, 0xBCACB364, 0x3A26A202,
            0x46E40370, 0xB5D74262, 0xE7FFC3AF, 0xF9C6A726, 0xB6EF19F5,
            0x456EFD1D, 0xA52210E0, 0x74C91FB9, 0xE9408834, 0xC1F17CE7,
            0x944A79D2, 0x87F17472, 0xBFC85D9A, 0x99898B79, 0x555F1352,
            0x9287F717, 0x821B8505, 0x9B675AA9, 0x6C66FF79, 0xF48B87DF,
            0x9904484C, 0x3E3861CC, 0xA0393660, 0xD7B8EA3A, 0x55CBD010,
            0xCA06470C, 0x16AE9277, 0x984178DA, 0xB777E797, 0xEF8173C9,
            0x56A3DE0C, 0x64F350E9, 0x0B2F54E0, 0x0896D4E6, 0x0246A097,
            0x4BD7FB97, 0xFA84F206, 0x2BE66C3E, 0x244930F4, 0xFCC2D994,
            0x9393570D, 0xAD0E9C60, 0x35725AE2, 0xDE775BF7, 0x0DBB87BC,
            0xF8A5E82C,
        }},
        {{
            0xD1A64E93, 0xD004558C, 0x433C2996, 0xE14A5DAF, 0xC13E20BB,
            0xFB5AC251, 0x1FBD4BA2, 0x07E414A5, 0x754EF2D0, 0xF6E31444,
            0x6A350F7C, 0xB5F45341, 0xC8005AE8, 0x903C0735, 0xB4487C1D,
            0x76411F84, 0x0E3E2536, 0x6B952D38, 0x96750A94, 0xDC7AF26B,
            0xD321B32C, 0x00020CC6, 0x3BEB8B44, 0x106486B7, 0xCAE518D3,
            0x1ACD54FD, 0x0D90713E, 0x97979922, 0xCDF948EC, 0xD567F27A,
            0x4F89BBBB, 0x25D35AD7, 0xA328B965, 0x930AC104, 0xBD126D37,
            0x1C16FD51, 0x163015A6, 0x8918C76C, 0xA68D6749, 0xAB3A9BE6,
            0xC9CDB56A, 0x050852BA, 0xA02344BE, 0x96C8EA51, 0xAE2DB0FF,
            0x8526CB11, 0xD763BC51, 0x85A06868, 0x6B159FCC, 0xA975A4E3,
            0xFAAC574E, 0xFA76B914, 0x920A15C4, 0x21DE09B2, 0xEACFF4D9,
            0x621EA993, 0xCFA5BF0A, 0xFA6123B3, 0xF4C65686, 0x84F32CDF,
            0xDE24ED75, 0x5D594450, 0xC898562B, 0x22E70FA0, 0xB9ADA330,
            0x891EEAD2, 0x1CF520F9, 0x3ED2ABB2, 0xA57B1527, 0xB616928A,
            0xDFEA23AA, 0xE4EF20BC, 0x99006D82, 0xB852A835, 0x93E6AA74,
            0xA0BCA025, 0xF9BA0440, 0xF60D2FE1, 0x4AC3BFC4, 0xA6884182,
            0x45DD3563, 0x543F95D9, 0x7A9187A8, 0xA4CAC0B4, 0xD6DEA497,
            0xEE7BDD29, 0x3227A33C, 0x2B1B249E, 0x1D6AF45D, 0x5546D960,
            0xCF9F4289, 0x15BBE6D3, 0x69FCAE11, 0x41D15DBB, 0xAA87AAFF,
            0xDA2E36ED, 0x324902DF, 0xAAC6326A, 0xA8A49066, 0x9877E4FD,
            0x7F78C4EA, 0x74DC2102, 0xF8352F71, 0x096850CF, 0x6C9267AD,
            0x9DE63A54, 0x230E2D83, 0x9441646E, 0x41858B4D, 0xA4E2133D,
            0x8DB8071D, 0x0BEAE6BC, 0x1DE565B0, 0x7A630757, 0x8A192DA7,
            0xCF66F778, 0x0149EF35, 0x90E276B9, 0x9FA45B04, 0x83500842,
            0xBA7ACF40, 0xA6F11455, 0x13C23786, 0x2F600CF3, 0xB9BA0E45,
            0xB2DD471D, 0x4B699AFB, 0x06AAD4AF, 0x36653DDB, 0xEAD16288,
            0x9D6E698C, 0x6A150793, 0x901735E1, 0x1648714A, 0x82A826E5,
            0xD617E704, 0x03075286, 0xCDF22348, 0xAD2F52F9, 0x1F88DEA9,
            0xA9D9FB50, 0x81924438, 0xD74BE0F4, 0x53707FCE, 0x7037D954,
            0x30BB392F, 0x983FFA5B, 0xFCF9AF16, 0x9D223945, 0x9CDC05A8,
            0x0B359DEF, 0xEE2BDB47, 0x55593CA4, 0x6525E8E1, 0x50FBC4BB,
            0x29EA560C, 0x359B0887, 0x44B4DDFC, 0xA994D923, 0xA1E66DF6,
            0x8D584C54, 0x0552F957, 0xF4A27911, 0x7AE967B8, 0x17C94D94,
            0x431B5EA7, 0x8B1089FA, 0x95A94B43, 0xECE3D707, 0xB59A5AFD,
            0x7AFCA1A2, 0x42B47862, 0xB8031F68, 0x0D54EDA3, 0xF4D78C68,
            0x7B4253FD, 0xA25CAD65, 0x644828DE, 0x2D112217, 0xC15A9F3D,
            0x7E8FF8FA, 0x09469606, 0xC01F24C5, 0xCFFB6E4B, 0x382E9C6E,
            0x6ACF8A9E, 0x585DD9C3, 0xF94B801C, 0x37B1578F, 0xC8C956EE,
            0xE16EC6A8, 0x1E9A491E, 0x5C0F9305, 0x7A452920, 0x947F0327,
            0x1883A346, 0x0DD69799, 0xE6246198, 0xE2543E43, 0x31D1CBC7,
            0x4E81B6FC, 0x58C07ECA, 0x3F087B9E, 0x3873748B, 0x7E75E816,
            0x31AF1EE5, 0x4CBCC3EE, 0x7CF9D3D4, 0x558F7981, 0xC47DB9DC,
            0xD803BAF2, 0xEAB022FD, 0xAC06D1B9, 0x305231EC, 0x756F15B6,
            0x2DD7DD88, 0xD6A74A46, 0x6B9E4141, 0xA5DBD4BA, 0xBBC274EA,
            0x8B66F111, 0x85E18002, 0x2D7B6928, 0x91ECBC23, 0xC26A9150,
            0x52F4615C, 0x79313F36, 0x235C4E36, 0x24EDFEA9, 0xDC8415E1,
            0x1E818A0D, 0x1100272A, 0xCA22DA05, 0x04894709, 0xB061A1F3,
            0x6874FDB9, 0xD09D8892, 0x2E3E374A, 0x8B99783E, 0x47BD571D,
            0x584DE2F3, 0x6AB7BAD2, 0x279F0E56, 0xA969052F, 0x0E006F6D,
            0x475A7246, 0x08332126, 0xC5A08674, 0x53650A95, 0x8E869C35,
            0x24D3D138, 0xB5C01352, 0x6533B0A6, 0x5A6F42B0, 0x9DA48984,
            0x4305FA01,
        }},
    }},
};

static constexpr KeyMaterial kKeyMaterial2 = KeyMaterial{
    .header = {{
        0x243F6A88,
        0x85A308D3,
        0x13198A2E,
        0x03707344,
        0xA4093822,
        0x299F31D0,
        0x082EFA98,
        0xEC4E6C89,
        0x452821E6,
        0x38D01377,
        0xBE5466CF,
        0x34E90C6C,
        0xC0AC29B7,
        0xC97C50DD,
        0x3F84D5B5,
        0xB5470917,
        0x9216D5D9,
        0x8979FB1B,
    }},
    .data = {{
        {{
            0xD1310BA6, 0x98DFB5AC, 0x2FFD72DB, 0xD01ADFB7, 0xB8E1AFED,
            0x6A267E96, 0xBA7C9045, 0xF12C7F99, 0x24A19947, 0xB3916CF7,
            0x0801F2E2, 0x858EFC16, 0x636920D8, 0x71574E69, 0xA458FEA3,
            0xF4933D7E, 0x0D95748F, 0x728EB658, 0x718BCD58, 0x82154AEE,
            0x7B54A41D, 0xC25A59B5, 0x9C30D539, 0x2AF26013, 0xC5D1B023,
            0x286085F0, 0xCA417918, 0xB8DB38EF, 0x8E79DCB0, 0x603A180E,
            0x6C9E0E8B, 0xB01E8A3E, 0xD71577C1, 0xBD314B27, 0x78AF2FDA,
            0x55605C60, 0xE65525F3, 0xAA55AB94, 0x57489862, 0x63E81440,
            0x55CA396A, 0x2AAB10B6, 0xB4CC5C34, 0x1141E8CE, 0xA15486AF,
            0x7C72E993, 0xB3EE1411, 0x636FBC2A, 0x2BA9C55D, 0x741831F6,
            0xCE5C3E16, 0x9B87931E, 0xAFD6BA33, 0x6C24CF5C, 0x7A325381,
            0x28958677, 0x3B8F4898, 0x6B4BB9AF, 0xC4BFE81B, 0x66282193,
            0x61D809CC, 0xFB21A991, 0x487CAC60, 0x5DEC8032, 0xEF845D5D,
            0xE98575B1, 0xDC262302, 0xEB651B88, 0x23893E81, 0xD396ACC5,
            0x0F6D6FF3, 0x83F44239, 0x2E0B4482, 0xA4842004, 0x69C8F04A,
            0x9E1F9B5E, 0x21C66842, 0xF6E96C9A, 0x670C9C61, 0xABD388F0,
            0x6A51A0D2, 0xD8542F68, 0x960FA728, 0xAB5133A3, 0x6EEF0B6C,
            0x137A3BE4, 0xBA3BF050, 0x7EFB2A98, 0xA1F1651D, 0x39AF0176,
            0x66CA593E, 0x82430E88, 0x8CEE8619, 0x456F9FB4, 0x7D84A5C3,
            0x3B8B5EBE, 0xE06F75D8, 0x85C12073, 0x401A449F, 0x56C16AA6,
            0x4ED3AA62, 0x363F7706, 0x1BFEDF72, 0x429B023D, 0x37D0D724,
            0xD00A1248, 0xDB0FEAD3, 0x49F1C09B, 0x075372C9, 0x80991B7B,
            0x25D479D8, 0xF6E8DEF7, 0xE3FE501A, 0xB6794C3B, 0x976CE0BD,
            0x04C006BA, 0xC1A94FB6, 0x409F60C4, 0x5E5C9EC2, 0x196A2463,
            0x68FB6FAF, 0x3E6C53B5, 0x1339B2EB, 0x3B52EC6F, 0x6DFC511F,
            0x9B30952C, 0xCC814544, 0xAF5EBD09, 0xBEE3D004, 0xDE334AFD,
            0x660F2807, 0x192E4BB3, 0xC0CBA857, 0x45C8740F, 0xD20B5F39,
            0xB9D3FBDB, 0x5579C0BD, 0x1A60320A, 0xD6A100C6, 0x402C7279,
            0x679F25FE, 0xFB1FA3CC, 0x8EA5E9F8, 0xDB3222F8, 0x3C7516DF,
            0xFD616B15, 0x2F501EC8, 0xAD0552AB, 0x323DB5FA, 0xFD238760,
            0x53317B48, 0x3E00DF82, 0x9E5C57BB, 0xCA6F8CA0, 0x1A87562E,
            0xDF1769DB, 0xD542A8F6, 0x287EFFC3, 0xAC6732C6, 0x8C4F5573,
            0x695B27B0, 0xBBCA58C8, 0xE1FFA35D, 0xB8F011A0, 0x10FA3D98,
            0xFD2183B8, 0x4AFCB56C, 0x2DD1D35B, 0x9A53E479, 0xB6F84565,
            0xD28E49BC, 0x4BFB9790, 0xE1DDF2DA, 0xA4CB7E33, 0x62FB1341,
            0xCEE4C6E8, 0xEF20CADA, 0x36774C01, 0xD07E9EFE, 0x2BF11FB4,
            0x95DBDA4D, 0xAE909198, 0xEAAD8E71, 0x6B93D5A0, 0xD08ED1D0,
            0xAFC725E0, 0x8E3C5B2F, 0x8E7594B7, 0x8FF6E2FB, 0xF2122B64,
            0x8888B812, 0x900DF01C, 0x4FAD5EA0, 0x688FC31C, 0xD1CFF191,
            0xB3A8C1AD, 0x2F2F2218, 0xBE0E1777, 0xEA752DFE, 0x8B021FA1,
            0xE5A0CC0F, 0xB56F74E8, 0x18ACF3D6, 0xCE89E299, 0xB4A84FE0,
            0xFD13E0B7, 0x7CC43B81, 0xD2ADA8D9, 0x165FA266, 0x80957705,
            0x93CC7314, 0x211A1477, 0xE6AD2065, 0x77B5FA86, 0xC75442F5,
            0xFB9D35CF, 0xEBCDAF0C, 0x7B3E89A0, 0xD6411BD3, 0xAE1E7E49,
            0x00250E2D, 0x2071B35E, 0x226800BB, 0x57B8E0AF, 0x2464369B,
            0xF009B91E, 0x5563911D, 0x59DFA6AA, 0x78C14389, 0xD95A537F,
            0x207D5BA2, 0x02E5B9C5, 0x83260376, 0x6295CFA9, 0x11C81968,
            0x4E734A41, 0xB3472DCA, 0x7B14A94A, 0x1B510052, 0x9A532915,
            0xD60F573F, 0xBC9BC6E4, 0x2B60A476, 0x81E67400, 0x08BA6FB5,
            0x571BE91F, 0xF296EC6B, 0x2A0DD915, 0xB6636521, 0xE7B9F9B6,
            0xFF34052E, 0xC5855664, 0x53B02D5D, 0xA99F8FA1, 0x08BA4799,
            0x6E85076A,
        }},
        {{
            0x4B7A70E9, 0xB5B32944, 0xDB75092E, 0xC4192623, 0xAD6EA6B0,
            0x49A7DF7D, 0x9CEE60B8, 0x8FEDB266, 0xECAA8C71, 0x699A17FF,
            0x5664526C, 0xC2B19EE1, 0x193602A5, 0x75094C29, 0xA0591340,
            0xE4183A3E, 0x3F54989A, 0x5B429D65, 0x6B8FE4D6, 0x99F73FD6,
            0xA1D29C07, 0xEFE830F5, 0x4D2D38E6, 0xF0255DC1, 0x4CDD2086,
            0x8470EB26, 0x6382E9C6, 0x021ECC5E, 0x09686B3F, 0x3EBAEFC9,
            0x3C971814, 0x6B6A70A1, 0x687F3584, 0x52A0E286, 0xB79C5305,
            0xAA500737, 0x3E07841C, 0x7FDEAE5C, 0x8E7D44EC, 0x5716F2B8,
            0xB03ADA37, 0xF0500C0D, 0xF01C1F04, 0x0200B3FF, 0xAE0CF51A,
            0x3CB574B2, 0x25837A58, 0xDC0921BD, 0xD19113F9, 0x7CA92FF6,
            0x94324773, 0x22F54701, 0x3AE5E581, 0x37C2DADC, 0xC8B57634,
            0x9AF3DDA7, 0xA9446146, 0x0FD0030E, 0xECC8C73E, 0xA4751E41,
            0xE238CD99, 0x3BEA0E2F, 0x3280BBA1, 0x183EB331, 0x4E548B38,
            0x4F6DB908, 0x6F420D03, 0xF60A04BF, 0x2CB81290, 0x24977C79,
            0x5679B072, 0xBCAF89AF, 0xDE9A771F, 0xD9930810, 0xB38BAE12,
            0xDCCF3F2E, 0x5512721F, 0x2E6B7124, 0x501ADDE6, 0x9F84CD87,
            0x7A584718, 0x7408DA17, 0xBC9F9ABC, 0xE94B7D8C, 0xEC7AEC3A,
            0xDB851DFA, 0x63094366, 0xC464C3D2, 0xEF1C1847, 0x3215D908,
            0xDD433B37, 0x24C2BA16, 0x12A14D43, 0x2A65C451, 0x50940002,
            0x133AE4DD, 0x71DFF89E, 0x10314E55, 0x81AC77D6, 0x5F11199B,
            0x043556F1, 0xD7A3C76B, 0x3C11183B, 0x5924A509, 0xF28FE6ED,
            0x97F1FBFA, 0x9EBABF2C, 0x1E153C6E, 0x86E34570, 0xEAE96FB1,
            0x860E5E0A, 0x5A3E2AB3, 0x771FE71C, 0x4E3D06FA, 0x2965DCB9,
            0x99E71D0F, 0x803E89D6, 0x5266C825, 0x2E4CC978, 0x9C10B36A,
            0xC6150EBA, 0x94E2EA78, 0xA5FC3C53, 0x1E0A2DF4, 0xF2F74EA7,
            0x361D2B3D, 0x1939260F, 0x19C27960, 0x5223A708, 0xF71312B6,
            0xEBADFE6E, 0xEAC31F66, 0xE3BC4595, 0xA67BC883, 0xB17F37D1,
            0x018CFF28, 0xC332DDEF, 0xBE6C5AA5, 0x65582185, 0x68AB9802,
            0xEECEA50F, 0xDB2F953B, 0x2AEF7DAD, 0x5B6E2F84, 0x1521B628,
            0x29076170, 0xECDD4775, 0x619F1510, 0x13CCA830, 0xEB61BD96,
            0x0334FE1E, 0xAA0363CF, 0xB5735C90, 0x4C70A239, 0xD59E9E0B,
            0xCBAADE14, 0xEECC86BC, 0x60622CA7, 0x9CAB5CAB, 0xB2F3846E,
            0x648B1EAF, 0x19BDF0CA, 0xA02369B9, 0x655ABB50, 0x40685A32,
            0x3C2AB4B3, 0x319EE9D5, 0xC021B8F7, 0x9B540B19, 0x875FA099,
            0x95F7997E, 0x623D7DA8, 0xF837889A, 0x97E32D77, 0x11ED935F,
            0x16681281, 0x0E358829, 0xC7E61FD6, 0x96DEDFA1, 0x7858BA99,
            0x57F584A5, 0x1B227263, 0x9B83C3FF, 0x1AC24696, 0xCDB30AEB,
            0x532E3054, 0x8FD948E4, 0x6DBC3128, 0x58EBF2EF, 0x34C6FFEA,
            0xFE28ED61, 0xEE7C3C73, 0x5D4A14D9, 0xE864B7E3, 0x42105D14,
            0x203E13E0, 0x45EEE2B6, 0xA3AAABEA, 0xDB6C4F15, 0xFACB4FD0,
            0xC742F442, 0xEF6ABBB5, 0x654F3B1D, 0x41CD2105, 0xD81E799E,
            0x86854DC7, 0xE44B476A, 0x3D816250, 0xCF62A1F2, 0x5B8D2646,
            0xFC8883A0, 0xC1C7B6A3, 0x7F1524C3, 0x69CB7492, 0x47848A0B,
            0x5692B285, 0x095BBF00, 0xAD19489D, 0x1462B174, 0x23820E00,
            0x58428D2A, 0x0C55F5EA, 0x1DADF43E, 0x233F7061, 0x3372F092,
            0x8D937E41, 0xD65FECF1, 0x6C223BDB, 0x7CDE3759, 0xCBEE7460,
            0x4085F2A7, 0xCE77326E, 0xA6078084, 0x19F8509E, 0xE8EFD855,
            0x61D99735, 0xA969A7AA, 0xC50C06C2, 0x5A04ABFC, 0x800BCADC,
            0x9E447A2E, 0xC3453484, 0xFDD56705, 0x0E1E9EC9, 0xDB73DBD3,
            0x105588CD, 0x675FDA79, 0xE3674340, 0xC5C43465, 0x713E38D8,
            0x3D28F89E, 0xF16DFF20, 0x153E21E7, 0x8FB03D4A, 0xE6E39F2B,
            0xDB83ADF7,
        }},
        {{
            0xE93D5A68, 0x948140F7, 0xF64C261C, 0x94692934, 0x411520F7,
            0x7602D4F7, 0xBCF46B2E, 0xD4A20068, 0xD4082471, 0x3320F46A,
            0x43B7D4B7, 0x500061AF, 0x1E39F62E, 0x97244546, 0x14214F74,
            0xBF8B8840, 0x4D95FC1D, 0x96B591AF, 0x70F4DDD3, 0x66A02F45,
            0xBFBC09EC, 0x03BD9785, 0x7FAC6DD0, 0x31CB8504, 0x96EB27B3,
            0x55FD3941, 0xDA2547E6, 0xABCA0A9A, 0x28507825, 0x530429F4,
            0x0A2C86DA, 0xE9B66DFB, 0x68DC1462, 0xD7486900, 0x680EC0A4,
            0x27A18DEE, 0x4F3FFEA2, 0xE887AD8C, 0xB58CE006, 0x7AF4D6B6,
            0xAACE1E7C, 0xD3375FEC, 0xCE78A399, 0x406B2A42, 0x20FE9E35,
            0xD9F385B9, 0xEE39D7AB, 0x3B124E8B, 0x1DC9FAF7, 0x4B6D1856,
            0x26A36631, 0xEAE397B2, 0x3A6EFA74, 0xDD5B4332, 0x6841E7F7,
            0xCA7820FB, 0xFB0AF54E, 0xD8FEB397, 0x454056AC, 0xBA489527,
            0x55533A3A, 0x20838D87, 0xFE6BA9B7, 0xD096954B, 0x55A867BC,
            0xA1159A58, 0xCCA92963, 0x99E1DB33, 0xA62A4A56, 0x3F3125F9,
            0x5EF47E1C, 0x9029317C, 0xFDF8E802, 0x04272F70, 0x80BB155C,
            0x05282CE3, 0x95C11548, 0xE4C66D22, 0x48C1133F, 0xC70F86DC,
            0x07F9C9EE, 0x41041F0F, 0x404779A4, 0x5D886E17, 0x325F51EB,
            0xD59BC0D1, 0xF2BCC18F, 0x41113564, 0x257B7834, 0x602A9C60,
            0xDFF8E8A3, 0x1F636C1B, 0x0E12B4C2, 0x02E1329E, 0xAF664FD1,
            0xCAD18115, 0x6B2395E0, 0x333E92E1, 0x3B240B62, 0xEEBEB922,
            0x85B2A20E, 0xE6BA0D99, 0xDE720C8C, 0x2DA2F728, 0xD0127845,
            0x95B794FD, 0x647D0862, 0xE7CCF5F0, 0x5449A36F, 0x877D48FA,
            0xC39DFD27, 0xF33E8D1E, 0x0A476341, 0x992EFF74, 0x3A6F6EAB,
            0xF4F8FD37, 0xA812DC60, 0xA1EBDDF8, 0x991BE14C, 0xDB6E6B0D,
            0xC67B5510, 0x6D672C37, 0x2765D43B, 0xDCD0E804, 0xF1290DC7,
            0xCC00FFA3, 0xB5390F92, 0x690FED0B, 0x667B9FFB, 0xCEDB7D9C,
            0xA091CF0B, 0xD9155EA3, 0xBB132F88, 0x515BAD24, 0x7B9479BF,
            0x763BD6EB, 0x37392EB3, 0xCC115979, 0x8026E297, 0xF42E312D,
            0x6842ADA7, 0xC66A2B3B, 0x12754CCC, 0x782EF11C, 0x6A124237,
            0xB79251E7, 0x06A1BBE6, 0x4BFB6350, 0x1A6B1018, 0x11CAEDFA,
            0x3D25BDD8, 0xE2E1C3C9, 0x44421659, 0x0A121386, 0xD90CEC6E,
            0xD5ABEA2A, 0x64AF674E, 0xDA86A85F, 0xBEBFE988, 0x64E4C3FE,
            0x9DBC8057, 0xF0F7C086, 0x60787BF8, 0x6003604D, 0xD1FD8346,
            0xF6381FB0, 0x7745AE04, 0xD736FCCC, 0x83426B33, 0xF01EAB71,
            0xB0804187, 0x3C005E5F, 0x77A057BE, 0xBDE8AE24, 0x55464299,
            0xBF582E61, 0x4E58F48F, 0xF2DDFDA2, 0xF474EF38, 0x8789BDC2,
            0x5366F9C3, 0xC8B38E74, 0xB475F255, 0x46FCD9B9, 0x7AEB2661,
            0x8B1DDF84, 0x846A0E79, 0x915F95E2, 0x466E598E, 0x20B45770,
            0x8CD55591, 0xC902DE4C, 0xB90BACE1, 0xBB8205D0, 0x11A86248,
            0x7574A99E, 0xB77F19B6, 0xE0A9DC09, 0x662D09A1, 0xC4324633,
            0xE85A1F02, 0x09F0BE8C, 0x4A99A025, 0x1D6EFE10, 0x1AB93D1D,
            0x0BA5A4DF, 0xA186F20F, 0x2868F169, 0xDCB7DA83, 0x573906FE,
            0xA1E2CE9B, 0x4FCD7F52, 0x50115E01, 0xA70683FA, 0xA002B5C4,
            0x0DE6D027, 0x9AF88C27, 0x773F8641, 0xC3604C06, 0x61A806B5,
            0xF0177A28, 0xC0F586E0, 0x006058AA, 0x30DC7D62, 0x11E69ED7,
            0x2338EA63, 0x53C2DD94, 0xC2C21634, 0xBBCBEE56, 0x90BCB6DE,
            0xEBFC7DA1, 0xCE591D76, 0x6F05E409, 0x4B7C0188, 0x39720A3D,
            0x7C927C24, 0x86E3725F, 0x724D9DB9, 0x1AC15BB4, 0xD39EB8FC,
            0xED545578, 0x08FCA5B5, 0xD83D7CD3, 0x4DAD0FC4, 0x1E50EF5E,
            0xB161E6F8, 0xA28514D9, 0x6C51133C, 0x6FD5C7E7, 0x56E14EC4,
            0x362ABFCE, 0xDDC6C837, 0xD79A3234, 0x92638212, 0x670EFA8E,
            0x406000E0,
        }},
        {{
            0x3A39CE37, 0xD3FAF5CF, 0xABC27737, 0x5AC52D1B, 0x5CB0679E,
            0x4FA33742, 0xD3822740, 0x99BC9BBE, 0xD5118E9D, 0xBF0F7315,
            0xD62D1C7E, 0xC700C47B, 0xB78C1B6B, 0x21A19045, 0xB26EB1BE,
            0x6A366EB4, 0x5748AB2F, 0xBC946E79, 0xC6A376D2, 0x6549C2C8,
            0x530FF8EE, 0x468DDE7D, 0xD5730A1D, 0x4CD04DC6, 0x2939BBDB,
            0xA9BA4650, 0xAC9526E8, 0xBE5EE304, 0xA1FAD5F0, 0x6A2D519A,
            0x63EF8CE2, 0x9A86EE22, 0xC089C2B8, 0x43242EF6, 0xA51E03AA,
            0x9CF2D0A4, 0x83C061BA, 0x9BE96A4D, 0x8FE51550, 0xBA645BD6,
            0x2826A2F9, 0xA73A3AE1, 0x4BA99586, 0xEF5562E9, 0xC72FEFD3,
            0xF752F7DA, 0x3F046F69, 0x77FA0A59, 0x80E4A915, 0x87B08601,
            0x9B09E6AD, 0x3B3EE593, 0xE990FD5A, 0x9E34D797, 0x2CF0B7D9,
            0x022B8B51, 0x96D5AC3A, 0x017DA67D, 0xD1CF3ED6, 0x7C7D2D28,
            0x1F9F25CF, 0xADF2B89B, 0x5AD6B472, 0x5A88F54C, 0xE029AC71,
            0xE019A5E6, 0x47B0ACFD, 0xED93FA9B, 0xE8D3C48D, 0x283B57CC,
            0xF8D56629, 0x79132E28, 0x785F0191, 0xED756055, 0xF7960E44,
            0xE3D35E8C, 0x15056DD4, 0x88F46DBA, 0x03A16125, 0x0564F0BD,
            0xC3EB9E15, 0x3C9057A2, 0x97271AEC, 0xA93A072A, 0x1B3F6D9B,
            0x1E6321F5, 0xF59C66FB, 0x26DCF319, 0x7533D928, 0xB155FDF5,
            0x03563482, 0x8ABA3CBB, 0x28517711, 0xC20AD9F8, 0xABCC5167,
            0xCCAD925F, 0x4DE81751, 0x3830DC8E, 0x379D5862, 0x9320F991,
            0xEA7A90C2, 0xFB3E7BCE, 0x5121CE64, 0x774FBE32, 0xA8B6E37E,
            0xC3293D46, 0x48DE5369, 0x6413E680, 0xA2AE0810, 0xDD6DB224,
            0x69852DFD, 0x09072166, 0xB39A460A, 0x6445C0DD, 0x586CDECF,
            0x1C20C8AE, 0x5BBEF7DD, 0x1B588D40, 0xCCD2017F, 0x6BB4E3BB,
            0xDDA26A7E, 0x3A59FF45, 0x3E350A44, 0xBCB4CDD5, 0x72EACEA8,
            0xFA6484BB, 0x8D6612AE, 0xBF3C6F47, 0xD29BE463, 0x542F5D9E,
            0xAEC2771B, 0xF64E6370, 0x740E0D8D, 0xE75B1357, 0xF8721671,
            0xAF537D5D, 0x4040CB08, 0x4EB4E2CC, 0x34D2466A, 0x0115AF84,
            0xE1B00428, 0x95983A1D, 0x06B89FB4, 0xCE6EA048, 0x6F3F3B82,
            0x3520AB82, 0x011A1D4B, 0x277227F8, 0x611560B1, 0xE7933FDC,
            0xBB3A792B, 0x344525BD, 0xA08839E1, 0x51CE794B, 0x2F32C9B7,
            0xA01FBAC9, 0xE01CC87E, 0xBCC7D1F6, 0xCF0111C3, 0xA1E8AAC7,
            0x1A908749, 0xD44FBD9A, 0xD0DADECB, 0xD50ADA38, 0x0339C32A,
            0xC6913667, 0x8DF9317C, 0xE0B12B4F, 0xF79E59B7, 0x43F5BB3A,
            0xF2D519FF, 0x27D9459C, 0xBF97222C, 0x15E6FC2A, 0x0F91FC71,
            0x9B941525, 0xFAE59361, 0xCEB69CEB, 0xC2A86459, 0x12BAA8D1,
            0xB6C1075E, 0xE3056A0C, 0x10D25065, 0xCB03A442, 0xE0EC6E0E,
            0x1698DB3B, 0x4C98A0BE, 0x3278E964, 0x9F1F9532, 0xE0D392DF,
            0xD3A0342B, 0x8971F21E, 0x1B0A7441, 0x4BA3348C, 0xC5BE7120,
            0xC37632D8, 0xDF359F8D, 0x9B992F2E, 0xE60B6F47, 0x0FE3F11D,
            0xE54CDA54, 0x1EDAD891, 0xCE6279CF, 0xCD3E7E6F, 0x1618B166,
            0xFD2C1D05, 0x848FD2C5, 0xF6FB2299, 0xF523F357, 0xA6327623,
            0x93A83531, 0x56CCCD02, 0xACF08162, 0x5A75EBB5, 0x6E163697,
            0x88D273CC, 0xDE966292, 0x81B949D0, 0x4C50901B, 0x71C65614,
            0xE6C6C7BD, 0x327A140A, 0x45E1D006, 0xC3F27B9A, 0xC9AA53FD,
            0x62A80F00, 0xBB25BFE2, 0x35BDD2F6, 0x71126905, 0xB2040222,
            0xB6CBCF7C, 0xCD769C2B, 0x53113EC0, 0x1640E3D3, 0x38ABBD60,
            0x2547ADF0, 0xBA38209C, 0xF746CE76, 0x77AFA1C5, 0x20756060,
            0x85CBFE4E, 0x8AE88DD8, 0x7AAAF9B0, 0x4CF9AA7E, 0x1948C25C,
            0x02FB8A8C, 0x01C36AE4, 0xD6EBE1F9, 0x90D4F869, 0xA65CDEA0,
            0x3F09252D, 0xC208E69F, 0xB74E6132, 0xCE77E25B, 0x578FDFE3,
            0x3AC372E6,
        }},
    }},
};

} // namespace ls_sec
