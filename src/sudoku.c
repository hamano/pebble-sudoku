/*
 * sudoku.c - sudoku for pebble watchapp
 * Copyright (c) 2014 HAMANO Tsukasa <code@cuspy.org>
 * This software is released under the MIT License
 */

#include <pebble.h>

static Window *window;
static TextLayer *text_layer;

static Layer *board_layer;
static GBitmap *mask_bmp;

#define BOARD_SIZE  140

#define BOX_SIZE {14, 14}
#define BOX_POS_1 2
#define BOX_POS_2 17
#define BOX_POS_3 32
#define BOX_POS_4 48
#define BOX_POS_5 63
#define BOX_POS_6 78
#define BOX_POS_7 94
#define BOX_POS_8 109
#define BOX_POS_9 124

const GRect boxes[] = {
    {{BOX_POS_1, BOX_POS_1}, BOX_SIZE},
    {{BOX_POS_2, BOX_POS_1}, BOX_SIZE},
    {{BOX_POS_3, BOX_POS_1}, BOX_SIZE},
    {{BOX_POS_4, BOX_POS_1}, BOX_SIZE},
    {{BOX_POS_5, BOX_POS_1}, BOX_SIZE},
    {{BOX_POS_6, BOX_POS_1}, BOX_SIZE},
    {{BOX_POS_7, BOX_POS_1}, BOX_SIZE},
    {{BOX_POS_8, BOX_POS_1}, BOX_SIZE},
    {{BOX_POS_9, BOX_POS_1}, BOX_SIZE},
    {{BOX_POS_1, BOX_POS_2}, BOX_SIZE},
    {{BOX_POS_2, BOX_POS_2}, BOX_SIZE},
    {{BOX_POS_3, BOX_POS_2}, BOX_SIZE},
    {{BOX_POS_4, BOX_POS_2}, BOX_SIZE},
    {{BOX_POS_5, BOX_POS_2}, BOX_SIZE},
    {{BOX_POS_6, BOX_POS_2}, BOX_SIZE},
    {{BOX_POS_7, BOX_POS_2}, BOX_SIZE},
    {{BOX_POS_8, BOX_POS_2}, BOX_SIZE},
    {{BOX_POS_9, BOX_POS_2}, BOX_SIZE},
    {{BOX_POS_1, BOX_POS_3}, BOX_SIZE},
    {{BOX_POS_2, BOX_POS_3}, BOX_SIZE},
    {{BOX_POS_3, BOX_POS_3}, BOX_SIZE},
    {{BOX_POS_4, BOX_POS_3}, BOX_SIZE},
    {{BOX_POS_5, BOX_POS_3}, BOX_SIZE},
    {{BOX_POS_6, BOX_POS_3}, BOX_SIZE},
    {{BOX_POS_7, BOX_POS_3}, BOX_SIZE},
    {{BOX_POS_8, BOX_POS_3}, BOX_SIZE},
    {{BOX_POS_9, BOX_POS_3}, BOX_SIZE},
    {{BOX_POS_1, BOX_POS_4}, BOX_SIZE},
    {{BOX_POS_2, BOX_POS_4}, BOX_SIZE},
    {{BOX_POS_3, BOX_POS_4}, BOX_SIZE},
    {{BOX_POS_4, BOX_POS_4}, BOX_SIZE},
    {{BOX_POS_5, BOX_POS_4}, BOX_SIZE},
    {{BOX_POS_6, BOX_POS_4}, BOX_SIZE},
    {{BOX_POS_7, BOX_POS_4}, BOX_SIZE},
    {{BOX_POS_8, BOX_POS_4}, BOX_SIZE},
    {{BOX_POS_9, BOX_POS_4}, BOX_SIZE},
    {{BOX_POS_1, BOX_POS_5}, BOX_SIZE},
    {{BOX_POS_2, BOX_POS_5}, BOX_SIZE},
    {{BOX_POS_3, BOX_POS_5}, BOX_SIZE},
    {{BOX_POS_4, BOX_POS_5}, BOX_SIZE},
    {{BOX_POS_5, BOX_POS_5}, BOX_SIZE},
    {{BOX_POS_6, BOX_POS_5}, BOX_SIZE},
    {{BOX_POS_7, BOX_POS_5}, BOX_SIZE},
    {{BOX_POS_8, BOX_POS_5}, BOX_SIZE},
    {{BOX_POS_9, BOX_POS_5}, BOX_SIZE},
    {{BOX_POS_1, BOX_POS_6}, BOX_SIZE},
    {{BOX_POS_2, BOX_POS_6}, BOX_SIZE},
    {{BOX_POS_3, BOX_POS_6}, BOX_SIZE},
    {{BOX_POS_4, BOX_POS_6}, BOX_SIZE},
    {{BOX_POS_5, BOX_POS_6}, BOX_SIZE},
    {{BOX_POS_6, BOX_POS_6}, BOX_SIZE},
    {{BOX_POS_7, BOX_POS_6}, BOX_SIZE},
    {{BOX_POS_8, BOX_POS_6}, BOX_SIZE},
    {{BOX_POS_9, BOX_POS_6}, BOX_SIZE},
    {{BOX_POS_1, BOX_POS_7}, BOX_SIZE},
    {{BOX_POS_2, BOX_POS_7}, BOX_SIZE},
    {{BOX_POS_3, BOX_POS_7}, BOX_SIZE},
    {{BOX_POS_4, BOX_POS_7}, BOX_SIZE},
    {{BOX_POS_5, BOX_POS_7}, BOX_SIZE},
    {{BOX_POS_6, BOX_POS_7}, BOX_SIZE},
    {{BOX_POS_7, BOX_POS_7}, BOX_SIZE},
    {{BOX_POS_8, BOX_POS_7}, BOX_SIZE},
    {{BOX_POS_9, BOX_POS_7}, BOX_SIZE},
    {{BOX_POS_1, BOX_POS_8}, BOX_SIZE},
    {{BOX_POS_2, BOX_POS_8}, BOX_SIZE},
    {{BOX_POS_3, BOX_POS_8}, BOX_SIZE},
    {{BOX_POS_4, BOX_POS_8}, BOX_SIZE},
    {{BOX_POS_5, BOX_POS_8}, BOX_SIZE},
    {{BOX_POS_6, BOX_POS_8}, BOX_SIZE},
    {{BOX_POS_7, BOX_POS_8}, BOX_SIZE},
    {{BOX_POS_8, BOX_POS_8}, BOX_SIZE},
    {{BOX_POS_9, BOX_POS_8}, BOX_SIZE},
    {{BOX_POS_1, BOX_POS_9}, BOX_SIZE},
    {{BOX_POS_2, BOX_POS_9}, BOX_SIZE},
    {{BOX_POS_3, BOX_POS_9}, BOX_SIZE},
    {{BOX_POS_4, BOX_POS_9}, BOX_SIZE},
    {{BOX_POS_5, BOX_POS_9}, BOX_SIZE},
    {{BOX_POS_6, BOX_POS_9}, BOX_SIZE},
    {{BOX_POS_7, BOX_POS_9}, BOX_SIZE},
    {{BOX_POS_8, BOX_POS_9}, BOX_SIZE},
    {{BOX_POS_9, BOX_POS_9}, BOX_SIZE},
};

static char *problems[] = {
"000000000000304000009102800001805700002703500073201940026000150037000290000000000",
"000000000001203400050060070080000090005000600900408005800030004410000032020000010",
"000000000013406920050000010025103740000805000038907150060000070041209530000000000",
"000000000016700000020800009037900000040207690052306070000008540200001030000003210",
"000000000032100490010020060000080050004305800020090000040060020051002370000000000",
"000000000057240009800009470009003000500900120003010900060000250000560000070000006",
"000000000072060100005100082080001300400000000037090010000023800504009000000000790",
"000000000096021034010043002000000000051000093082000061000000000020087009043012058",
"000000000900000084062300050000600045300010006000900070000100000405002000030800009",
"000000040002004001070050090003007000040060000600100800020000100850900060000080003",
"000000071020800000000403000700060050000200300900000000600070000080000400000050000",
"000000082008500093050400000094100000000000000000008210000009060240005900860000000",
"000000401800200000000607000000800060040000300010000000600000020050010000700030000",
"000000520080400000030009000501000600200700000000300000600010000000000704000000030",
"000000580003700009060050003080030000005102400000070050800020040500008700041000000",
"000000801600200000000705000000600020010000300080000000200000070030080000500040000",
"000000801600200000000705000000600020010000300080000000200000070040080000500030000",
"000000801700200000000506000000700050010000300080000000500000020030080000600040000",
"000000801700200000000506000000700050010000300080000000500000020040080000600030000",
"000000940000090005300005070080400100463000000000007080800700000700000028050260000",
"000002000000070001700300090800700000020890600013006000090050824000008910000000000",
"000004700008350000010000506090008007050000030700500040907000020000023800005700000",
"000007095000001000860020000020073008500000060003004900305000417240000000000000000",
"000010780500009000000000040020000000000600003074080000000003002080040010600500000",
"000014000030000200070000000000900030601000000000000080200000104000050600000708000",
"000030000003010400010496020006000100734000269002000700020389010001020500000060000",
"000030090000200001050900000000000000102080406080500020075000000401006003000004060",
"000040000000109000006050300070201030300000002020000010703000601060708090102030405",
"000050001100000070060000080000004000009010300000596020080062007007000000305070200",
"000060004006030000100400507700000805000800000608000090002090000400003200009700100",
"000070080006000500020003061010007002008005340200900000002000000580006030400010000",
"000075000010020000040003000500000302000800010000000600000100480200000000700000000",
"000080000000701000003060500020507080905000302070809010004050600000203000000010000",
"000090000000104000000807000008040500004010200050302010030401020607080901102030405",
"000090000604000905005078400000800600901000703003001000007560300506000802000080000",
"000090001051000030060100500008506000200010006000207400007003010010000290900080000",
"000102700002000560035000082406000005007000000000008900600000007210000003040003210",
"000360000850000000904008000000006800000000017009004500010500060400009002000003000",
"000432100005000000000675000000000800008519000000000000300806079600901302042003001",
"000500000000000506970000020004802000250100030080030000000004070013050090020003100",
"000501000090000800060000000401000000000070090000000030800000105000200400000360000",
"000503000000060700508000016360020000000401000000030005670000208004070000000200500",
"000520000090003004000000700010000040080045300600010008702000000008000032040080010",
"000570090063040051070001200300010800720934015001060002004100060180050420050027000",
"000658000004000000120000000000009607000300500002080003001900800306000004000047300",
"000703000870010059010000070043000820200000001095000640030000060520060017000502000",
"000800009087300040600700000008500970000000000043007500000003000030001450400002001",
"000801039040050002000002608680004725020567010715300064407100000100090080830206000",
"000890003057300192093027080906000000010004000205000000031085020084200531000710006",
"000903000003000200040050010100507009007060100800102003020010080005000600000708000",
"000943000001080600079000430700000003010000050024000980800050006030809040007312800",
"001506300020070080700000005800000002010907030200000009900000001080040070003102500",
"002007003030008020400090000000000084006000500290000000000040005080500030300600900",
"002470058000000000000001040000020009528090400009000100000000030300007500685002000",
"003000000074000000120043000000620400008104600005038000000270056000000190000000200",
"003000100012040980574010236000704000037020590000809000391070825065080470008000600",
"003000500000020000600104009001406200400030001005802700100709002000050000006000300",
"005000987040050001007000000200048000090100000600200000300600200000009070000000500",
"005008001800000090000000780000400000640000900000053002060000000001380050000907140",
"005070100000000000908000702060000010400801007030090060704030501000502000001000800",
"005070200080502040600080003070000010401000806060000090800010004090706030004020500",
"005090400090080030407000609000508000580000063000902000609000504050070020004050700",
"005802400700000003200905008004000700080000030006000800300206009800000005009508300",
"005900000010070020000208006001809502020000040504302100800403000040020030000001700",
"006000000123450000007000056708010090309080000000009300030000004610000003000003210",
"006000500405126307073508620000205000500090002000804000032601850801359206007000900",
"006003700020050010100400002002100008080070090500004600900005004040060080005800900",
"006800700080010030400509001008070100200000007005030200600901004040000020009000500",
"007008000006020300030000009010050060000010000070900002000000004083004000260000510",
"008000436700352100930600500000517000000000071000924000610200700800796300009000268",
"008090100060500020000006000030107050000000009004000300050000200070003080200700004",
"008400030000300000900001574790008000000007005140000020009060002050000400000090056",
"009000003000009000700000506006500400000300000028000000300750600600000000000120308",
"009400000020060090108009205500040000010500483004006000002050100090070020005010004",
"010000080700120003500000006000030000009040030020005001000806000100070004063000210",
"012300000000000059000000062456780000000000000000090700830010405521000003000003210",
"012307050000000903000000470456780009000000000100009267043000005201000004060804321",
"020000000000600003074080000000003002080040010600500000000010780500009000000000040",
"020000000305062009068000300050000000000640802004700900003000001000006000170430000",
"020000006000041000007800001000000700003700000600412000010074005008050070000003900",
"020000593800500460940060008002030000060080730700200000000040380070000600000000005",
"020030050300501006008000300070305080600000002030204090007000200100402005090080040",
"020300000006008090830500000000200080709005000000006004000000010001000402200700809",
"020300000063000005800000001500009030000700000000100008087900260000006070006007004",
"020400007500000900800920050005000080000040000060000300040097005002000009300008060",
"020978010300000007001203400050060070800000009400000008103702504540010032200000001",
"023700006800060590900000700000040970307096002000000000500470000000002000080000000",
"026000009400800060500900300054069000000000000000570480002005007090004005700000230",
"026039000000600001900000700000004009050000200008500000300200900400007620000000004",
"030050090840630210000000000004001003065043021000000000700800900102304506000000000",
"032000005800300000904280001000400039000600050000010000020006708000004000095000060",
"032008140400100380500000060067000000000800000300905008016003504000001032043602001",
"032100050400000087056000000000700800298006570000000200000000400005410302040020010",
"037500092040200018015400300070800000026301780000007020008002140490005030150004260",
"040050067000100040000200000100800300000000200060000000000040050300000800200000000",
"040080020000301000805000409090030050300908006080020010509000804000703000060050090",
"040500000800090030076020000014600000000009007000003600001004050060000003007100200",
"047020000800001000030000902000005000600810050000040000070000304000900010400270800",
"047080001000000000000600700600003570000005000010060000280040000090100040000020690",
"047600050803000002000009000000805006000100000602400000078000510006000040090004007",
"050006200600300000002000009070008005009020300300700090400000800000005007006200040",
"050008030800000009001067800020000000030000000040090000005002600400000008670403021",
"050090000100000600000308000008040009514000000030000200000000004080006007700150060",
"050307040100000000030000000508030610000800509060010000000040006000692700002000900",
"050600002408010050060700000802000000070000090000000804000008070080090506300004010",
"050816090804030701000020000039000610200304009000201008043002007100003006762100450",
"052006800000007020000000600004800900200410000001000008006100380000090006300600109",
"052400000000070100000000000000802000300000600090500000106030000000000089700000000",
"060308070000040000430010095640050012000000000720000034190020047000030000004701900",
"060501090100090053900007000040800070000000508081705030000050200000000000076008000",
"060800030090047020100000004000400300450030012002010000800000090040056070030200001",
"065000000700400002812300000900000000073001500000000080000009840000010030040003201",
"070000080150000073004709100003201500000080000007604200009508700410000069020000010",
"080004050000700300000000000010085000600000200000040000302600000000000041700000000",
"080040000300000010000000020005000406900100800200000000000309000060000500000200000",
"083400000000070050000000000040108000000000027000300000206050000500000800000000100",
"092300000000080100000000000107040000000000065800000000060502000400000700000900000",
"098010000200000060000000000000302050084000000000600000000040809300500000000000100",
"100000003060300700070005001210700090007000000008010020000806400009020060000400000",
"100000308060400000000000000203010000000000075800000000070500060000080200040000000",
"100000308060400000000000000203010000000000095800000000050600070000080200040000000",
"100000308070400000000000000203010000000000095800000000050600070000080200040000000",
"100000709040007200800000000070010060300000005060040020000000008005300070702000046",
"100000900064001070070040000000300000308900500007000020000060709000004010000129030",
"100005009200000670360000000407000000500000300000087591000090003001000020030200100",
"100006080064000000000040007000090600070400500500070100050000320300008000400000000",
"100007860007008010800200009000000002400010000009005000608000000000050900000009304",
"100020060304050002607080000090400000000000000000006150000003004500001320043002001",
"120080076600102003090060020700408009002000700010070030500709002201000804030020050",
"120090800000002004340500000000600000987005360000000080000001540001000030050403210",
"150000000206000000307902000480605000000301080000489201000000400000000302020000010",
"150000640206000000307090000480106000000389000000702301000000403000000020032000010",
"150300000070040200004072000008000000000900108010080790000003800000000000600007423",
"160000000207001000380040900409007000530000000000000300000800607002010430000300201",
"160002840207000095380964000400006000500070200000100700000421500710000400054600321",
"200001090010030700900800020000000850060400000000070003020300060000500000109000205",
"200060000070000090000123000004506700708000906003702100000241000010000020000030001",
"200060009000971000000000000012000340500607008009000050030000500876503421000000000",
"203080000800700000000000100060507000400000030000100000000000082050000600010000000",
"249060003030000200800000005000006000000200000010040820090500700004000001070003000",
"290000046700060008001234500400176005006080400010090020000523000300010002028000310",
"300000007060000050008000400000901000000040000040302010602010703090807060504030201",
"300080000000700005100000000000000360002004000070000000000060130045200000000000800",
"300405006074601350001080400780102063010050040060000010000209000009000700020000080",
"306070000000000051800000000010405000700000600000200000020000040000080300000500000",
"340600000007000000020080570000005000070010020000400000036020010000000900000007082",
"380600000009000000020030510000005000030010060000400000017050080000000900000007032",
"400000300000802000000700000000100087340000000600000000500060000000010400082000000",
"400000508030000000000700000020000060000050800000010000000603070500200000108000000",
"400000805030000000000700000020000060000050400000010000000603070500200000109000000",
"400000805030000000000700000020000060000080400000010000000603070500200000104000000",
"400070100001904605000001000000700002002030000847006000014000806020000300600090000",
"400080602610724000003000000791006080040075300835001070007000000980152000100030908",
"406500000007040008008300000009020000005100000020003500080009030060001020053402100",
"450000030000801000090000000000050090200700000800000000010040000000000702000600800",
"450792086960040023001080400700604001624010379800907002006050200340060018580173064",
"480300000000000071020000000705000060000200800000000000001076000300000400000050000",
"500000709070004080902070300080403000009000800000809040004080607050600010807000005",
"520006000000000701300000000000400800600000050000000000041800000000030020008700000",
"530020900024030050009000000000010827000700000000098100000000000006400009102050430",
"600000703040800000000000000000504080700200000103000000020000050000070900000010000",
"600000803040700000000000000000504070300200000106000000020000050000080600000010000",
"600302000010000050000000000702600000000000084300000000080150000000080200000000700",
"600302000040000010000000000702600000000000054300000000080150000000040200000000700",
"600302000040000080000000000702600000000000054300000000080150000000080200000000700",
"600302000050000010000000000702600000000000054300000000080150000000040200000000700",
"600701004020030010001000700400000009050090030100000002004000600010080050900307008",
"602050000000003040000000000430008000010000200000000700500270000000000081000600000",
"602050000000004030000000000430008000010000200000000700500270000000000081000600000",
"700304006060020070009000200400908003050000040600407002003000400040070030800603005",
"800001000002300090010040670000050020000600030007000010089210543000000000540003201",
"800005000000069700000700040005300076020050030380002900030004000006280000000900003",
"800700004050000600000000000030970008000043005000020900006000000200060007071008302",
"900010203000004560000078094000009810000060902080000000501000300000301020000020001",
"900060008000200900005001760050300600700080009006002040012600400003007000400050003",
"904005000250600100310000008070009000400260000001470000700000002000300806040000090",
"950607028040000010230000094300020009000104000000080000003000600080000050400315002",
"963000000100008000000205000040800000010000700000030025700000030009020407000000900",
};

char state[82];

static int problem_size = sizeof(problems) / sizeof(problems[0]);
static int problem_id;

static char *problem;
static int cursor;

static int is_uniq(char *tuple){
    int i, n;
    char uniq[10];
    memset(uniq, 0, sizeof(uniq));
    for(i=0; i<9; i++){
        n = tuple[i] - '0';
        if(n <= 0 || 9 < n){
            return 0;
        }
        if(uniq[n]){
            return 0;
        }else{
            uniq[n] = 1;
        }
    }
    return 1;
}

static int is_solved(){
    int i, x, y;
    char tuple[10];
    tuple[9] = '\0';
    if(strchr(state, '0')){
        return 0;
    }
    for(y = 0; y<9; y++){
        for(x = 0; x<9; x++){
            i = (y * 9) + x;
            tuple[x] = state[i];
        }
        if(!is_uniq(tuple)){
            return 0;
        }
    }
    for(x = 0; x<9; x++){
        for(y = 0; y<9; y++){
            i = (y * 9) + x;
            tuple[x] = state[i];
        }
        if(!is_uniq(tuple)){
            return 0;
        }
    }
    return 1;
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "select_click_handler()");
    if(problem[cursor] == '0'){
        state[cursor]++;
        if (state[cursor] > '9') {
            state[cursor] = '0';
        }
        if (is_solved()) {
            layer_set_hidden((Layer *)text_layer, false);
        }
        layer_mark_dirty(board_layer);
    }
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "up_click_handler()");
    cursor += 1;
    cursor %= 81;
    layer_mark_dirty(board_layer);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "down_click_handler()");
    cursor += 9;
    cursor %= 81;
    layer_mark_dirty(board_layer);
}

static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void board_update_proc(Layer *layer, GContext *ctx) {
    //GRect bounds = layer_get_bounds(layer);
    //GPoint center = GPoint(bounds.size.w / 2, (bounds.size.h / 2));
    int i;
    char num[2] = {0};
    GRect box;
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "board_update_proc()");
    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_fill_rect(ctx, GRect(0, 0, BOARD_SIZE, BOARD_SIZE),
                       0, GCornerNone);

    for(i=0; i<81; i++){
        graphics_context_set_fill_color(ctx, GColorWhite);
        graphics_fill_rect(ctx, boxes[i], 0, GCornerNone);
        if(problem[i] != '0'){
            graphics_draw_bitmap_in_rect(ctx, mask_bmp, boxes[i]);
        }
    }

    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_fill_rect(ctx, boxes[cursor], 0, GCornerNone);

    for(i=0; i<81; i++){
        if(state[i] == '0'){
            continue;
        }

        num[0] = state[i];
        if(i == cursor){
            graphics_context_set_text_color(ctx, GColorWhite);
        }else{
            graphics_context_set_text_color(ctx, GColorBlack);
        }
        box = boxes[i];
        box.origin.y -= 5;
        graphics_draw_text(ctx,
                           num,
                           fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD),
                           box,
                           GTextOverflowModeFill,
                           GTextAlignmentCenter,
                           NULL);
    }

}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    APP_LOG(APP_LOG_LEVEL_DEBUG,
            "window_load: bounds=(%d, %d)\n", bounds.size.w, bounds.size.h);

    board_layer = layer_create(GRect(2, 2, BOARD_SIZE+2, BOARD_SIZE+2));
    layer_add_child(window_layer, board_layer);
    layer_set_update_proc(board_layer, board_update_proc);

    text_layer = text_layer_create((GRect){
            .origin = { 2, 64 },
            .size = { BOARD_SIZE-4, 20 }
        });
    text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
    text_layer_set_text(text_layer, "Congratulations!");
    layer_set_hidden((Layer *)text_layer, true);
    layer_add_child(board_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
    text_layer_destroy(text_layer);
}

static void init(void) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "init()");
    window = window_create();
    window_set_click_config_provider(window, click_config_provider);
    window_set_window_handlers(window, (WindowHandlers) {
            .load = window_load,
            .unload = window_unload,
    });
    const bool animated = true;
    window_stack_push(window, animated);
}

static void deinit(void) {
    window_destroy(window);
    if(mask_bmp){
        gbitmap_destroy(mask_bmp);
    }
}

static void init_sudoku(void) {
    srand(time(NULL));
    problem_id = rand() % problem_size;
    APP_LOG(APP_LOG_LEVEL_DEBUG,
            "problem id/size: %d/%d\n", problem_id, problem_size);
    problem = problems[problem_id];
    strncpy(state, problem, 82);
    mask_bmp = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MASK);
}

int main(void) {
    init_sudoku();
    init();
    APP_LOG(APP_LOG_LEVEL_DEBUG,
            "Done initializing, pushed window: %p", window);
    app_event_loop();
    deinit();
}