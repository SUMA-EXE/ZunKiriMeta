#include <Arduboy2.h>
#include "bitmap.h"
#include "misaki_font.h"

Arduboy2 arduboy;


#define ARDBITMAP_SBUF arduboy.getBuffer()//突っ込むバッファ
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;//ビットマップの奴

uint8_t TIME=0;//時間
uint8_t KiriA;//きりたんの目
uint8_t ZunA;//ずんだもんの目
uint8_t MetaA;//めたんの目

uint8_t Kiri_on;//きりたんオン
uint8_t Zun_on;//ずんだもんオン
uint8_t Meta_on;//めたんオン

uint8_t KiriM;//きりたんの口
uint8_t ZunM;//ずんだもんの口
uint8_t MetaM;//めたんの口

uint8_t ZunMimi;//ずんだもんの耳
uint8_t Y=0;//キャラクターY座標
uint8_t X=36;//71;//きりたんX
int X2=-66;//1;//ずんだもんX
uint8_t X3=128;//62;//めたんX

uint8_t X_n;//きりたん移動先X
int X2_n;//ずんだもん移動先X
uint8_t X3_n;//めたん移動先X

uint8_t mode=0;//ゲームモード
uint8_t Tk=0;//メッセージ表示
uint8_t select_x=0;
uint8_t select_y=0;
uint8_t select_P1=0;
uint8_t select_P2=0;
uint8_t select_M=0;

uint8_t Back_C;//戻るカウント

uint8_t tiyousi=0;//調子

uint8_t mes_time=0;
boolean mes_PM=false;


uint8_t talk_turn=0;//トーク番
uint8_t talk_pa=0;//パターン


uint8_t talk_Pt=0;//トーク番

uint8_t Tk_C=0;//トークカウンター
uint8_t Tk_P=0;//トークプレイヤ
uint8_t Tk_L=0;//トーク長さ


uint8_t Tk_QC=0;//トークカウンター

uint8_t Word_No=0;//ワードナンバー
uint8_t Word_SSR=0;//ワード感想切り替え
uint8_t Word_SSR2=0;//ワード感想切り替え
uint8_t Word_1=0;//ワード
uint8_t Word_2=0;//ワード
uint8_t Word_K=0;//ワード感想

uint8_t KAI=0;//会話
uint8_t KAIZ=0;//前回の会話
uint8_t RR=0;//
uint8_t RRRR=0;//

uint8_t date_No=0;

uint8_t Q_dateM[22]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;//クイズ作成用
uint8_t Q_date[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;//クイズデータ
uint8_t Q_Z[7]={0,0,0,0,0,0,0};//クイズずらし用
uint8_t Q_H[7]={0,0,0,0,0,0,0};//クイズヒント出す順
uint8_t Q_HZ[7]={0,0,0,0,0,0,0};//クイズヒントずらし
uint8_t QQQ=0;
uint8_t Q_keep=0;//クイズキープ
uint8_t Q_A=0;//クイズ答え
uint8_t Q_Ten=0;//点数
uint8_t Q_End=0;//答え発表

//モードせんたく
PROGMEM const uint8_t mesMode[] ={ 0xf0, 0xd7,0xee,0xbe,0x5d,0x95,0x61,0x51, };
//フリーモード
PROGMEM const uint8_t mesFree[] ={ 0xf0, 0xca,0xdf,0xee,0xd7,0xee,0xbe, };
//トークモード
PROGMEM const uint8_t mesTalk[] ={ 0xf0, 0xbd,0xee,0xa4,0xd7,0xee,0xbe, };

//フリー
PROGMEM const uint8_t mesFree2[] ={ 0xf0, 0xca,0xdf,0xee, };
//トーク
PROGMEM const uint8_t mesTalk2[] ={ 0xf0, 0xbd,0xee,0xa4, };
//クイズ
PROGMEM const uint8_t mesQ[] ={ 0xf0, 0xa4,0x99,0xaf, };

//→
PROGMEM const uint8_t mesMigi[] ={ 0xf0, 0x35, };
//きりたん
PROGMEM const uint8_t mesKiri[] ={ 0xf0, 0x4f,0x8c,0x61,0x95, };
//ずんだもん
PROGMEM const uint8_t mesZun[] ={ 0xf0, 0x5c,0x95,0x62,0x84,0x95, };
//めたん
PROGMEM const uint8_t mesMeta[] ={ 0xf0, 0x83,0x61,0x95, };
//めたんさん
PROGMEM const uint8_t mesMeta2[] ={ 0xf0, 0x83,0x61,0x95,0x57,0x95, };

//だれをよびますか？
PROGMEM const uint8_t mesDare[] ={ 0xf0, 0x62,0x8e,0x94,0x8a,0x75,0x80,0x5b,0x4d,0x08, };
//ひとりめ
PROGMEM const uint8_t mes1Ban[] ={ 0xf0, 0x74,0x6a,0x8c,0x83, };
//ふたりめ
PROGMEM const uint8_t mes2Ban[] ={ 0xf0, 0x77,0x61,0x8c,0x83, };
//ひとりだけ
PROGMEM const uint8_t mes1Dake[] ={ 0xf0, 0x74,0x6a,0x8c,0x62,0x53, };

//これでいいですか？
PROGMEM const uint8_t mesKorede[] ={ 0xf0, 0x55,0x8e,0x69,0x46,0x46,0x69,0x5b,0x4d,0x08, };
//はい
PROGMEM const uint8_t mesHai[] ={ 0xf0, 0x71,0x46, };
//ちがう
PROGMEM const uint8_t mesTiga[] ={ 0xf0, 0x63,0x4e,0x48, };

//きり
PROGMEM const uint8_t mesKiriN[] ={ 0xf0, 0x4f,0x8c, };
//ずん
PROGMEM const uint8_t mesZunN[] ={ 0xf0, 0x5c,0x95, };
//めた
PROGMEM const uint8_t mesMetaN[] ={ 0xf0, 0x83,0x61, };

//こんにちは、とうほくきりたんです　きょうもがんばりましょうね
PROGMEM const uint8_t mesTest1[] ={ 0xf0, 0x55,0x95,0x6d,0x63,0x71,0x01,0x6a,0x48,0x7d,0x51,0x4f,0x8c,0x61,0x95,0x69,0x5b,0x00,0x4f,0x89,0x48,0x84,0x4e,0x95,0x72,0x8c,0x80,0x59,0x89,0x48,0x6f, };
//こんにちは、わたくしはしこくめたんよ　きょうはひえるみたいね
PROGMEM const uint8_t mesTest2[] ={ 0xf0, 0x55,0x95,0x6d,0x63,0x71,0x01,0x91,0x61,0x51,0x59,0x71,0x59,0x55,0x51,0x83,0x61,0x95,0x8a,0x00,0x4f,0x89,0x48,0x71,0x74,0x4a,0x8d,0x81,0x61,0x46,0x6f, };
//こんにちはなのだ　ずんだもんなのだ！　いっしょにあそぶのだ！
PROGMEM const uint8_t mesTest3[] ={ 0xf0, 0x55,0x95,0x6d,0x63,0x71,0x6c,0x70,0x62,0x00,0x5c,0x95,0x62,0x84,0x95,0x6c,0x70,0x62,0x09,0x00,0x46,0x65,0x59,0x89,0x6d,0x44,0x5f,0x78,0x70,0x62,0x09, };

//じかんもあることですし　すこしおはなししませんか？
PROGMEM const uint8_t mesQA1[] ={ 0xf0, 0x5a,0x4d,0x95,0x84,0x44,0x8d,0x55,0x6a,0x69,0x5b,0x59,0x00,0x5b,0x55,0x59,0x4c,0x71,0x6c,0x59,0x59,0x80,0x5d,0x95,0x4d,0x08, };
//すこしはなしがあるんだけど　いまちょっといいかしら？
PROGMEM const uint8_t mesQA2[] ={ 0xf0, 0x5b,0x55,0x59,0x71,0x6c,0x59,0x4e,0x44,0x8d,0x95,0x62,0x53,0x6b,0x00,0x46,0x80,0x63,0x89,0x65,0x6a,0x46,0x46,0x4d,0x59,0x8b,0x08, };
//ひまなのだ　なにか　ずんだもんとおはなしするのだ！
PROGMEM const uint8_t mesQA3[] ={ 0xf0, 0x74,0x80,0x6c,0x70,0x62,0x00,0x6c,0x6d,0x4d,0x00,0x5c,0x95,0x62,0x84,0x95,0x6a,0x4c,0x71,0x6c,0x59,0x5b,0x8d,0x70,0x62,0x09, };

//かまいませんよ　わたしもじかんつぶしてたところです
PROGMEM const uint8_t mesQAA1[] ={ 0xf0, 0x4d,0x80,0x46,0x80,0x5d,0x95,0x8a,0x00,0x91,0x61,0x59,0x84,0x5a,0x4d,0x95,0x66,0x78,0x59,0x68,0x61,0x6a,0x55,0x8f,0x69,0x5b, };
//いいわよ！わたしくしも　じかんをもてあましていたところよ
PROGMEM const uint8_t mesQAA2[] ={ 0xf0, 0x46,0x46,0x91,0x8a,0x09,0x91,0x61,0x59,0x51,0x59,0x84,0x00,0x5a,0x4d,0x95,0x94,0x84,0x68,0x44,0x80,0x59,0x68,0x46,0x61,0x6a,0x55,0x8f,0x8a, };
//だいじょうぶなのだ！ずんだもんもひまだったのだ！
PROGMEM const uint8_t mesQAA3[] ={ 0xf0, 0x62,0x46,0x5a,0x89,0x48,0x78,0x6c,0x70,0x62,0x09,0x5c,0x95,0x62,0x84,0x95,0x84,0x74,0x80,0x62,0x65,0x61,0x70,0x62,0x09, };

//ですか？
PROGMEM const uint8_t mesDesuka[] ={ 0xf0, 0x69,0x5b,0x4d,0x08, };
//かしら？
PROGMEM const uint8_t mesKasira[] ={ 0xf0, 0x4d,0x59,0x8b,0x08, };
//なのだ？
PROGMEM const uint8_t mesNanodaH[] ={ 0xf0, 0x6c,0x70,0x62,0x08, };

//です
PROGMEM const uint8_t mesDesu[] ={ 0xf0, 0x69,0x5b, };
//よ
PROGMEM const uint8_t mesYo[] ={ 0xf0, 0x8a, };
//なのだ！
PROGMEM const uint8_t mesNanodaB[] ={ 0xf0, 0x6c,0x70,0x62,0x09, };

//のだ！
PROGMEM const uint8_t mesNodaB[] ={ 0xf0, 0x70,0x62,0x09, };

//こんにちは
PROGMEM const uint8_t mesHi[] ={ 0xf0, 0x55,0x95,0x6d,0x63,0x71, };
//こんにちはなのだ！
PROGMEM const uint8_t mesHiN[] ={ 0xf0, 0x55,0x95,0x6d,0x63,0x71,0x6c,0x70,0x62,0x09, };

//さいきんちょうしは　どう
PROGMEM const uint8_t mesSaikin[] ={ 0xf0, 0x57,0x46,0x4f,0x95,0x63,0x89,0x48,0x59,0x71,0x00,0x6b,0x48, };

//まあまあ
PROGMEM const uint8_t mesMama[] ={ 0xf0, 0x80,0x44,0x80,0x44, };
//いまいち
PROGMEM const uint8_t mesBoti[] ={ 0xf0, 0x46,0x80,0x46,0x63, };
//げんき
PROGMEM const uint8_t mesGenki[] ={ 0xf0, 0x54,0x95,0x4f, };

//は
PROGMEM const uint8_t mesWa[] ={ 0xf0, 0x71, };
//って
PROGMEM const uint8_t mesTe[] ={ 0xf0, 0x65,0x68, };

//どうおもってる
PROGMEM const uint8_t mesDou[] ={ 0xf0, 0x6b,0x48,0x4c,0x84,0x65,0x68,0x8d, };
//んですか？
PROGMEM const uint8_t mesSuka1[] ={ 0xf0, 0x95,0x69,0x5b,0x4d,0x08, };
//のかしら？
PROGMEM const uint8_t mesSuka2[] ={ 0xf0, 0x70,0x4d,0x59,0x8b,0x08, };
//のだ？
PROGMEM const uint8_t mesSuka3[] ={ 0xf0, 0x70,0x62,0x08, };

//ですよね
PROGMEM const uint8_t mesDesuyone[] ={ 0xf0, 0x69,0x5b,0x8a,0x6f, };
//よね
PROGMEM const uint8_t mesYone[] ={ 0xf0, 0x8a,0x6f, };

//そうですね　わたしもそうおもいます
PROGMEM const uint8_t mesSouKoutei1[] ={ 0xf0, 0x5f,0x48,0x69,0x5b,0x6f,0x00,0x91,0x61,0x59,0x84,0x5f,0x48,0x4c,0x84,0x46,0x80,0x5b, };
//そうですか？わたしは
PROGMEM const uint8_t mesSouWatasi1[] ={ 0xf0, 0x5f,0x48,0x69,0x5b,0x4d,0x08,0x91,0x61,0x59,0x71, };
//とおもいますね
PROGMEM const uint8_t mesOmoimasu1[] ={ 0xf0, 0x6a,0x4c,0x84,0x46,0x80,0x5b,0x6f, };
//っていえば
PROGMEM const uint8_t mesTeIeba[] ={ 0xf0, 0x65,0x68,0x46,0x4a,0x72, };
//そういえば
PROGMEM const uint8_t mesSouie[] ={ 0xf0, 0x5f,0x48,0x46,0x4a,0x72, };
//もありますよね
PROGMEM const uint8_t mesMoari[] ={ 0xf0, 0x84,0x44,0x8c,0x80,0x5b,0x8a,0x6f, };
//もそうですよね
PROGMEM const uint8_t mesMosou[] ={ 0xf0, 0x84,0x5f,0x48,0x69,0x5b,0x8a,0x6f, };

//そうね　わたくしもそうおもうわ
PROGMEM const uint8_t mesSouKoutei12[] ={ 0xf0, 0x5f,0x48,0x6f,0x00,0x91,0x61,0x51,0x59,0x84,0x5f,0x48,0x4c,0x84,0x48,0x91, };
//そうかしら　
PROGMEM const uint8_t mesSouWatasi12[] ={ 0xf0, 0x5f,0x48,0x4d,0x59,0x8b,0x00, };
//のがあってるとおもうわ
PROGMEM const uint8_t mesOmoimasu12[] ={ 0xf0, 0x70,0x4e,0x44,0x65,0x68,0x8d,0x6a,0x4c,0x84,0x48,0x91, };
//なら
PROGMEM const uint8_t mesTeIeba2[] ={ 0xf0, 0x6c,0x8b, };
//もありかしらね
PROGMEM const uint8_t mesMoari2[] ={ 0xf0, 0x84,0x44,0x8c,0x4d,0x59,0x8b,0x6f, };
//もそうよね
PROGMEM const uint8_t mesMosou2[] ={ 0xf0, 0x84,0x5f,0x48,0x8a,0x6f, };

//そうなのだ　ぼくもそうおもうのだ
PROGMEM const uint8_t mesSouKoutei13[] ={ 0xf0, 0x5f,0x48,0x6c,0x70,0x62,0x00,0x7e,0x51,0x84,0x5f,0x48,0x4c,0x84,0x48,0x70,0x62, };
//ちがうのだ！　それは
PROGMEM const uint8_t mesSouWatasi13[] ={ 0xf0, 0x63,0x4e,0x48,0x70,0x62,0x09,0x00,0x5f,0x8e,0x71, };
//もそうだとおもうのだ
PROGMEM const uint8_t mesMoari3[] ={ 0xf0, 0x84,0x5f,0x48,0x62,0x6a,0x4c,0x84,0x48,0x70,0x62, };
//もありだとおもうのだ
PROGMEM const uint8_t mesMosou3[] ={ 0xf0, 0x84,0x44,0x8c,0x62,0x6a,0x4c,0x84,0x48,0x70,0x62, };


//あっ！もうこんなじかんですね
PROGMEM const uint8_t mesEndK1[] ={ 0xf0, 0x44,0x65,0x09,0x84,0x48,0x55,0x95,0x6c,0x5a,0x4d,0x95,0x69,0x5b,0x6f, };
//あれ？もうこんなじかんね
PROGMEM const uint8_t mesEndM1[] ={ 0xf0, 0x44,0x8e,0x08,0x84,0x48,0x55,0x95,0x6c,0x5a,0x4d,0x95,0x6f, };
//そろそろおやつのじかんなのだ！
PROGMEM const uint8_t mesEndZ1[] ={ 0xf0, 0x5f,0x8f,0x5f,0x8f,0x4c,0x86,0x66,0x70,0x5a,0x4d,0x95,0x6c,0x70,0x62,0x09, };
//そうですね　そろそろおひらきにしますか
PROGMEM const uint8_t mesEndK2[] ={ 0xf0, 0x5f,0x48,0x69,0x5b,0x6f,0x00,0x5f,0x8f,0x5f,0x8f,0x4c,0x74,0x8b,0x4f,0x6d,0x59,0x80,0x5b,0x4d, };
//そうね　なごりおしいけどそろそろおわりね
PROGMEM const uint8_t mesEndM2[] ={ 0xf0, 0x5f,0x48,0x6f,0x00,0x6c,0x56,0x8c,0x4c,0x59,0x46,0x53,0x6b,0x5f,0x8f,0x5f,0x8f,0x4c,0x91,0x8c,0x6f, };
//そうなのだ！そろそろかえるのだ！
PROGMEM const uint8_t mesEndZ2[] ={ 0xf0, 0x5f,0x48,0x6c,0x70,0x62,0x09,0x5f,0x8f,0x5f,0x8f,0x4d,0x4a,0x8d,0x70,0x62,0x09, };
//ではまた、さようなら
PROGMEM const uint8_t mesEndK3[] ={ 0xf0, 0x69,0x71,0x80,0x61,0x01,0x57,0x8a,0x48,0x6c,0x8b, };
//じゃあ、またね
PROGMEM const uint8_t mesEndM3[] ={ 0xf0, 0x5a,0x85,0x44,0x01,0x80,0x61,0x6f, };
//バイバイなのだ！
PROGMEM const uint8_t mesEndZ3[] ={ 0xf0, 0xc5,0x99,0xc5,0x99,0x6c,0x70,0x62,0x09, };

//ここはクイズコーナーなのだ！
PROGMEM const uint8_t mesQQ1[] ={ 0xf0, 0x55,0x55,0x71,0xa4,0x99,0xaf,0xa8,0xee,0xbf,0xee,0x6c,0x70,0x62,0x09, };
//わたしたちがヒントをだすのでクイズにこたえてくださいね
PROGMEM const uint8_t mesQQ2[] ={ 0xf0, 0x91,0x61,0x59,0x61,0x63,0x4e,0xc7,0xe8,0xbd,0x94,0x62,0x5b,0x70,0x69,0xa4,0x99,0xaf,0x6d,0x55,0x61,0x4a,0x68,0x51,0x62,0x57,0x46,0x6f, };
//はやくこたえるとポイントがおおくもらえるわよ
PROGMEM const uint8_t mesQQ3[] ={ 0xf0, 0x71,0x86,0x51,0x55,0x61,0x4a,0x8d,0x6a,0xd2,0x99,0xe8,0xbd,0x4e,0x4c,0x4c,0x51,0x84,0x8b,0x4a,0x8d,0x91,0x8a, };
//ぜんぶで７もんなのだ！がんばるのだ！
PROGMEM const uint8_t mesQQ4[] ={ 0xf0, 0x5e,0x95,0x78,0x69,0x40,0x84,0x95,0x6c,0x70,0x62,0x09,0x4e,0x95,0x72,0x8d,0x70,0x62,0x09, };
//では、そろそろはじめるますね
PROGMEM const uint8_t mesQQ5[] ={ 0xf0, 0x69,0x71,0x01,0x5f,0x8f,0x5f,0x8f,0x71,0x5a,0x83,0x8d,0x80,0x5b,0x6f, };

//○
PROGMEM const uint8_t mesMaru[] ={ 0xf0, 0x28, };
//×
PROGMEM const uint8_t mesBatu[] ={ 0xf0, 0x15, };
//　　　　　
PROGMEM const uint8_t mesWhite[] ={ 0xf0, 0x00,0x00,0x00,0x00,0x00, };


//クイズしゅうりょうです
PROGMEM const uint8_t mesQ_end_K_1[] ={ 0xf0, 0xa4,0x99,0xaf,0x59,0x87,0x48,0x8c,0x89,0x48,0x69,0x5b, };
//こんかいのけっかは　　　てんです
PROGMEM const uint8_t mesQ_end_K_2[] ={ 0xf0, 0x55,0x95,0x4d,0x46,0x70,0x53,0x65,0x4d,0x71,0x00,0x00,0x00,0x68,0x95,0x69,0x5b, };

//すごいです！わたしこんなてんすうみたことないです！
PROGMEM const uint8_t mesQ_end_K_3[] ={ 0xf0, 0x5b,0x56,0x46,0x69,0x5b,0x09,0x91,0x61,0x59,0x55,0x95,0x6c,0x68,0x95,0x5b,0x48,0x81,0x61,0x55,0x6a,0x6c,0x46,0x69,0x5b,0x09, };

//さすがですね！でもわたしもほんきだせばこれくらいけますよ
PROGMEM const uint8_t mesQ_end_K_4[] ={ 0xf0, 0x57,0x5b,0x4e,0x69,0x5b,0x6f,0x09,0x69,0x84,0x91,0x61,0x59,0x84,0x7d,0x95,0x4f,0x62,0x5d,0x72,0x55,0x8e,0x51,0x8b,0x46,0x53,0x80,0x5b,0x8a, };

//おしいですね　もうすこしがんばりましょうね
PROGMEM const uint8_t mesQ_end_K_5[] ={ 0xf0, 0x4c,0x59,0x46,0x69,0x5b,0x6f,0x00,0x84,0x48,0x5b,0x55,0x59,0x4e,0x95,0x72,0x8c,0x80,0x59,0x89,0x48,0x6f, };

//まだまだですね　もうすこしおべんきょうしたほうがいいですね
PROGMEM const uint8_t mesQ_end_K_6[] ={ 0xf0, 0x80,0x62,0x80,0x62,0x69,0x5b,0x6f,0x00,0x84,0x48,0x5b,0x55,0x59,0x4c,0x7b,0x95,0x4f,0x89,0x48,0x59,0x61,0x7d,0x48,0x4e,0x46,0x46,0x69,0x5b,0x6f, };

//やるきあるんですか？ダメダメですね
PROGMEM const uint8_t mesQ_end_K_7[] ={ 0xf0, 0x86,0x8d,0x4f,0x44,0x8d,0x95,0x69,0x5b,0x4d,0x08,0xb5,0xd6,0xb5,0xd6,0x69,0x5b,0x6f, };

//クイズしゅうりょうね
PROGMEM const uint8_t mesQ_end_M_1[] ={ 0xf0, 0xa4,0x99,0xaf,0x59,0x87,0x48,0x8c,0x89,0x48,0x6f, };
//こんかいのけっかは　　　てんよ
PROGMEM const uint8_t mesQ_end_M_2[] ={ 0xf0, 0x55,0x95,0x4d,0x46,0x70,0x53,0x65,0x4d,0x71,0x00,0x00,0x00,0x68,0x95,0x8a, };

//すごいわ！あなたてんさいね！わたくしのかんぱいよ
PROGMEM const uint8_t mesQ_end_M_3[] ={ 0xf0, 0x5b,0x56,0x46,0x91,0x09,0x44,0x6c,0x61,0x68,0x95,0x57,0x46,0x6f,0x09,0x91,0x61,0x51,0x59,0x70,0x4d,0x95,0x73,0x46,0x8a, };

//さすがね！わたくしのライバルにみとめてあげるわ！
PROGMEM const uint8_t mesQ_end_M_4[] ={ 0xf0, 0x57,0x5b,0x4e,0x6f,0x09,0x91,0x61,0x51,0x59,0x70,0xde,0x99,0xc5,0xe0,0x6d,0x81,0x6a,0x83,0x68,0x44,0x54,0x8d,0x91,0x09, };

//もうすこしだったわね　つぎのクイズまってるわ！
PROGMEM const uint8_t mesQ_end_M_5[] ={ 0xf0, 0x84,0x48,0x5b,0x55,0x59,0x62,0x65,0x61,0x91,0x6f,0x00,0x66,0x50,0x70,0xa4,0x99,0xaf,0x80,0x65,0x68,0x8d,0x91,0x09, };

//べんきょうぶそくだったみたいね　つぎはがんばりなさい
PROGMEM const uint8_t mesQ_end_M_6[] ={ 0xf0, 0x7b,0x95,0x4f,0x89,0x48,0x78,0x5f,0x51,0x62,0x65,0x61,0x81,0x61,0x46,0x6f,0x00,0x66,0x50,0x71,0x4e,0x95,0x72,0x8c,0x6c,0x57,0x46, };

//なさけないわね　クイズやるきあるのかしら？
PROGMEM const uint8_t mesQ_end_M_7[] ={ 0xf0, 0x6c,0x57,0x53,0x6c,0x46,0x91,0x6f,0x00,0xa4,0x99,0xaf,0x86,0x8d,0x4f,0x44,0x8d,0x70,0x4d,0x59,0x8b,0x08, };

//クイズしゅーりょーなのだ！
PROGMEM const uint8_t mesQ_end_Z_1[] ={ 0xf0, 0xa4,0x99,0xaf,0x59,0x87,0xee,0x8c,0x89,0xee,0x6c,0x70,0x62,0x09, };
//こんかいのけっかは　　　なのだ！
PROGMEM const uint8_t mesQ_end_Z_2[] ={ 0xf0, 0x55,0x95,0x4d,0x46,0x70,0x53,0x65,0x4d,0x71,0x00,0x00,0x00,0x6c,0x70,0x62,0x09, };

//すごいのだ！こんやおいわいのパーティーなのだ！
PROGMEM const uint8_t mesQ_end_Z_3[] ={ 0xf0, 0x5b,0x56,0x46,0x70,0x62,0x09,0x55,0x95,0x86,0x4c,0x46,0x91,0x46,0x70,0xc6,0xee,0xbb,0x98,0xee,0x6c,0x70,0x62,0x09, };

//さすがなのだ！ずんだもんよりかしこいのだ！
PROGMEM const uint8_t mesQ_end_Z_4[] ={ 0xf0, 0x57,0x5b,0x4e,0x6c,0x70,0x62,0x09,0x5c,0x95,0x62,0x84,0x95,0x8a,0x8c,0x4d,0x59,0x55,0x46,0x70,0x62,0x09, };

//おしかったのだ！あともうすこしなのだ！
PROGMEM const uint8_t mesQ_end_Z_5[] ={ 0xf0, 0x4c,0x59,0x4d,0x65,0x61,0x70,0x62,0x09,0x44,0x6a,0x84,0x48,0x5b,0x55,0x59,0x6c,0x70,0x62,0x09, };

//どんまいなのだ！ずんだもんがおーえんしてるからがんばるのだ！
PROGMEM const uint8_t mesQ_end_Z_6[] ={ 0xf0, 0x6b,0x95,0x80,0x46,0x6c,0x70,0x62,0x09,0x5c,0x95,0x62,0x84,0x95,0x4e,0x4c,0xee,0x4a,0x95,0x59,0x68,0x8d,0x4d,0x8b,0x4e,0x95,0x72,0x8d,0x70,0x62,0x09, };

//だいじょうぶなのだ？どこかぐあいでもわるいのだ？
PROGMEM const uint8_t mesQ_end_Z_7[] ={ 0xf0, 0x62,0x46,0x5a,0x89,0x48,0x78,0x6c,0x70,0x62,0x08,0x6b,0x55,0x4d,0x52,0x44,0x46,0x69,0x84,0x91,0x8d,0x46,0x70,0x62,0x08, };


//ワード
//きりたんぽ
PROGMEM const uint8_t ward1[] ={ 0xf0, 0x4f,0x8c,0x61,0x95,0x7f, };
//ずんだ
PROGMEM const uint8_t ward2[] ={ 0xf0, 0x5c,0x95,0x62, };
//カレー
PROGMEM const uint8_t ward3[] ={ 0xf0, 0xa0,0xe1,0xee, };
//タンポポ
PROGMEM const uint8_t ward4[] ={ 0xf0, 0xb4,0xe8,0xd2,0xd2, };
//ドリル
PROGMEM const uint8_t ward5[] ={ 0xf0, 0xbe,0xdf,0xe0, };
//エビフライ
PROGMEM const uint8_t ward6[] ={ 0xf0, 0x9d,0xc8,0xca,0xde,0x99, };
//あおじる
PROGMEM const uint8_t ward7[] ={ 0xf0, 0x44,0x4c,0x5a,0x8d, };
//カブトムシ
PROGMEM const uint8_t ward8[] ={ 0xf0, 0xa0,0xcb,0xbd,0xd5,0xac, };
//ふともも
PROGMEM const uint8_t ward9[] ={ 0xf0, 0x77,0x6a,0x84,0x84, };
//あんこもち
PROGMEM const uint8_t ward10[] ={ 0xf0, 0x44,0x95,0x55,0x84,0x63, };
//きんようび
PROGMEM const uint8_t ward11[] ={ 0xf0, 0x4f,0x95,0x8a,0x48,0x75, };
//ほのお
PROGMEM const uint8_t ward12[] ={ 0xf0, 0x7d,0x70,0x4c, };
//げつようび
PROGMEM const uint8_t ward13[] ={ 0xf0, 0x54,0x66,0x8a,0x48,0x75, };
//もち
PROGMEM const uint8_t ward14[] ={ 0xf0, 0x84,0x63, };
//まくら
PROGMEM const uint8_t ward15[] ={ 0xf0, 0x80,0x51,0x8b, };
//つくし
PROGMEM const uint8_t ward16[] ={ 0xf0, 0x66,0x51,0x59, };
//りんご
PROGMEM const uint8_t ward17[] ={ 0xf0, 0x8c,0x95,0x56, };
//パソコン
PROGMEM const uint8_t ward18[] ={ 0xf0, 0xc6,0xb2,0xa8,0xe8, };
//どうじんし
PROGMEM const uint8_t ward19[] ={ 0xf0, 0x6b,0x48,0x5a,0x95,0x59, };
//ウナギ
PROGMEM const uint8_t ward20[] ={ 0xf0, 0x9b,0xbf,0xa3, };
//ムーン
PROGMEM const uint8_t ward21[] ={ 0xf0, 0xd5,0xee,0xe8, };
//ポテト
PROGMEM const uint8_t ward22[] ={ 0xf0, 0xd2,0xbb,0xbd, };


//おいしい
PROGMEM const uint8_t wardD1[] ={ 0xf0, 0x4c,0x46,0x59,0x46, };
//ふつう
PROGMEM const uint8_t wardD2[] ={ 0xf0, 0x77,0x66,0x48, };
//にがて
PROGMEM const uint8_t wardD3[] ={ 0xf0, 0x6d,0x4e,0x68, };
//やわらかい
PROGMEM const uint8_t wardD4[] ={ 0xf0, 0x86,0x91,0x8b,0x4d,0x46, };
//たのしい
PROGMEM const uint8_t wardD5[] ={ 0xf0, 0x61,0x70,0x59,0x46, };
//カッコいい
PROGMEM const uint8_t wardD6[] ={ 0xf0, 0xa0,0xb8,0xa8,0x46,0x46, };
//ほそい
PROGMEM const uint8_t wardD7[] ={ 0xf0, 0x7d,0x5f,0x46, };
//みどり
PROGMEM const uint8_t wardD8[] ={ 0xf0, 0x81,0x6b,0x8c, };
//ちゃいろ
PROGMEM const uint8_t wardD9[] ={ 0xf0, 0x63,0x85,0x46,0x8f, };
//きいろ
PROGMEM const uint8_t wardD10[] ={ 0xf0, 0x4f,0x46,0x8f, };
//もっちり
PROGMEM const uint8_t wardD11[] ={ 0xf0, 0x84,0x65,0x63,0x8c, };
//うすい
PROGMEM const uint8_t wardD12[] ={ 0xf0, 0x48,0x5b,0x46, };
//あかい
PROGMEM const uint8_t wardD13[] ={ 0xf0, 0x44,0x4d,0x46, };
//しろい
PROGMEM const uint8_t wardD14[] ={ 0xf0, 0x59,0x8f,0x46, };
//ようび
PROGMEM const uint8_t wardD15[] ={ 0xf0, 0x8a,0x48,0x75, };




//日本語
void drawText(uint8_t x, uint8_t y, const uint8_t *mes, uint8_t cnt,uint8_t Wb)
{
  uint8_t pb;
  uint8_t page;
  uint8_t screen_start = 0;
  uint8_t screen_end = 128;
  

  if (x < screen_start) {
    x = screen_start;
  }
  
  for (uint8_t i = 0; i < cnt; i++) {
    pb = pgm_read_byte_near(mes + i);

    switch (pb) {
      case MISAKI_FONT_F0_PAGE:
        page = MISAKI_FONT_F0_PAGE;
        continue;
      case MISAKI_FONT_F1_PAGE:
        page = MISAKI_FONT_F1_PAGE;
        continue;
      case MISAKI_FONT_F2_PAGE:
        page = MISAKI_FONT_F2_PAGE;
        continue;
    }

    if (!page) {
      continue;
    }

    switch (page) {
      #ifdef MISAKI_FONT_F0_H
        case MISAKI_FONT_F0_PAGE:
          if (pb > MISAKI_FONT_F0_SIZE) {
            continue;
          }      
          if ((x + 8) > screen_end) {
            x = screen_start;   
            y = y + 8;
          }
          arduboy.drawBitmap(x, y,  misaki_font_f0[ pb ], MISAKI_FONT_F0_W, 8, Wb);
          x = x + 8;    
          break;
      #endif
      #ifdef MISAKI_FONT_F1_H
        case MISAKI_FONT_F1_PAGE:
          if (pb > MISAKI_FONT_F1_SIZE) {
            continue;
          }      
          if ((x + 4) > screen_end) {
            x = screen_start;   
            y = y + 8;
          }
          arduboy.drawBitmap(x, y,  misaki_font_f1[ pb ], MISAKI_FONT_F1_W, 8, Wb);
          arduboy.drawBitmap(x + 3, y, misaki_font_0x00, 1, 8, Wb);
          x = x + 4;  
          break;
      #endif
      #ifdef MISAKI_FONT_F2_H
        case MISAKI_FONT_F2_PAGE:
          if (pb > MISAKI_FONT_F2_SIZE) {
            continue;
          }      
          if ((x + 8) > screen_end) {
            x = screen_start;   
            y = y + 8;
          }
          arduboy.drawBitmap(x, y,  misaki_font_f2[ pb ], MISAKI_FONT_F2_W, 8, Wb);
          arduboy.drawBitmap(x + 7, y, misaki_font_0x00, 1, 8, Wb);
          x = x + 8;    
          break;
      #endif
    }
  }
}


void Word_Draw(uint8_t Wx, uint8_t Wn,uint8_t Wty)
{//文字描写
  
  arduboy.setCursor(0,0);
  //arduboy.print(Wn);
  if (Wty==0){
  if (Wn==1){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward1, sizeof(ward1),WHITE);}
  if (Wn==2){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward2, sizeof(ward2),WHITE);}
  if (Wn==3){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward3, sizeof(ward3),WHITE);}
  if (Wn==4){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward4, sizeof(ward4),WHITE);}
  if (Wn==5){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward5, sizeof(ward5),WHITE);}
  if (Wn==6){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward6, sizeof(ward6),WHITE);}
  if (Wn==7){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward7, sizeof(ward7),WHITE);}
  if (Wn==8){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward8, sizeof(ward8),WHITE);}
  if (Wn==9){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward9, sizeof(ward9),WHITE);}
  if (Wn==10){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward10, sizeof(ward10),WHITE);}
  if (Wn==11){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward11, sizeof(ward11),WHITE);}
  if (Wn==12){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward12, sizeof(ward12),WHITE);}
  if (Wn==13){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward13, sizeof(ward13),WHITE);}
  if (Wn==14){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward14, sizeof(ward14),WHITE);}
  if (Wn==15){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward15, sizeof(ward15),WHITE);}
  if (Wn==16){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward16, sizeof(ward16),WHITE);}
  if (Wn==17){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward17, sizeof(ward17),WHITE);}
  if (Wn==18){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward18, sizeof(ward18),WHITE);}
  if (Wn==19){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward19, sizeof(ward19),WHITE);}
  if (Wn==20){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward20, sizeof(ward20),WHITE);}
  if (Wn==21){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward21, sizeof(ward21),WHITE);}
  if (Wn==22){ drawText((Wx%16)*8, 48+(Wx/16)*8, ward22, sizeof(ward22),WHITE);}
  }
  if (Wty==1){
  if (Wn==1){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD1, sizeof(wardD1),WHITE);}
  if (Wn==2){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD2, sizeof(wardD2),WHITE);}
  if (Wn==3){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD3, sizeof(wardD3),WHITE);}
  if (Wn==4){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD4, sizeof(wardD4),WHITE);}
  if (Wn==5){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD5, sizeof(wardD5),WHITE);}
  if (Wn==6){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD6, sizeof(wardD6),WHITE);}
  if (Wn==7){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD7, sizeof(wardD7),WHITE);}
  if (Wn==8){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD8, sizeof(wardD8),WHITE);}
  if (Wn==9){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD9, sizeof(wardD9),WHITE);}
  if (Wn==10){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD10, sizeof(wardD10),WHITE);}
  if (Wn==11){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD11, sizeof(wardD11),WHITE);}
  if (Wn==12){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD12, sizeof(wardD12),WHITE);}
  if (Wn==13){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD13, sizeof(wardD13),WHITE);}
  if (Wn==14){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD14, sizeof(wardD14),WHITE);}
  if (Wn==15){ drawText((Wx%16)*8, 48+(Wx/16)*8, wardD15, sizeof(wardD15),WHITE);}
  }
  if (Wn==50){ drawText((Wx%16)*8, 48+(Wx/16)*8, mesWhite, sizeof(mesWhite),WHITE);}
  return;
}


uint8_t Date_W(uint8_t A, uint8_t B)
{
if (A==1 and B==0){return 7 ;};if (A==1 and B==1){return 1 ;};if (A==1 and B==2){return 1 ;};if (A==1 and B==3){return 2 ;};
if (A==2 and B==0){return 8 ;};if (A==2 and B==1){return 1 ;};if (A==2 and B==2){return 1 ;};if (A==2 and B==3){return 1 ;};
if (A==3 and B==0){return 9 ;};if (A==3 and B==1){return 2 ;};if (A==3 and B==2){return 1 ;};if (A==3 and B==3){return 1 ;};
if (A==4 and B==0){return 10;};if (A==4 and B==1){return 3 ;};if (A==4 and B==2){return 1 ;};if (A==4 and B==3){return 3 ;};
if (A==5 and B==0){return 7 ;};if (A==5 and B==1){return 2 ;};if (A==5 and B==2){return 6 ;};if (A==5 and B==3){return 6 ;};
if (A==6 and B==0){return 9 ;};if (A==6 and B==1){return 2 ;};if (A==6 and B==2){return 1 ;};if (A==6 and B==3){return 1 ;};
if (A==7 and B==0){return 8 ;};if (A==7 and B==1){return 3 ;};if (A==7 and B==2){return 1 ;};if (A==7 and B==3){return 3 ;};
if (A==8 and B==0){return 9 ;};if (A==8 and B==1){return 3 ;};if (A==8 and B==2){return 2 ;};if (A==8 and B==3){return 6 ;};
if (A==9 and B==0){return 11;};if (A==9 and B==1){return 4 ;};if (A==9 and B==2){return 2 ;};if (A==9 and B==3){return 2 ;};
if (A==10 and B==0){return 11;};if (A==10 and B==1){return 2 ;};if (A==10 and B==2){return 1 ;};if (A==10 and B==3){return 3 ;};
if (A==11 and B==0){return 15;};if (A==11 and B==1){return 5 ;};if (A==11 and B==2){return 2 ;};if (A==11 and B==3){return 2 ;};
if (A==12 and B==0){return 13;};if (A==12 and B==1){return 2 ;};if (A==12 and B==2){return 6 ;};if (A==12 and B==3){return 2 ;};
if (A==13 and B==0){return 15;};if (A==13 and B==1){return 3 ;};if (A==13 and B==2){return 2 ;};if (A==13 and B==3){return 2 ;};
if (A==14 and B==0){return 14;};if (A==14 and B==1){return 11;};if (A==14 and B==2){return 1 ;};if (A==14 and B==3){return 4 ;};
if (A==15 and B==0){return 14;};if (A==15 and B==1){return 4 ;};if (A==15 and B==2){return 12 ;};if (A==15 and B==3){return 4;};
if (A==16 and B==0){return 7 ;};if (A==16 and B==1){return 3 ;};if (A==16 and B==2){return 1 ;};if (A==16 and B==3){return 3 ;};
if (A==17 and B==0){return 13;};if (A==17 and B==1){return 1 ;};if (A==17 and B==2){return 1 ;};if (A==17 and B==3){return 2 ;};
if (A==18 and B==0){return 12;};if (A==18 and B==1){return 5 ;};if (A==18 and B==2){return 2 ;};if (A==18 and B==3){return 2 ;};
if (A==19 and B==0){return 12;};if (A==19 and B==1){return 1 ;};if (A==19 and B==2){return 2 ;};if (A==19 and B==3){return 3 ;};
if (A==20 and B==0){return 7 ;};if (A==20 and B==1){return 1 ;};if (A==20 and B==2){return 1 ;};if (A==20 and B==3){return 1 ;};
if (A==21 and B==0){return 10;};if (A==21 and B==1){return 2 ;};if (A==21 and B==2){return 6 ;};if (A==21 and B==3){return 2 ;};
if (A==22 and B==0){return 10;};if (A==22 and B==1){return 1 ;};if (A==22 and B==2){return 1 ;};if (A==22 and B==3){return 2 ;};


return 0;
};

uint8_t Word_S(uint8_t DNo,uint8_t tY,uint8_t No2_)
{//言葉サーチ用
  uint8_t RRR=random(44);
  uint8_t WSA=0;
  uint8_t No3=0;
  uint8_t i=0;
  //repeat
  //Date_W(Word_No,0)
  if (No2_!=1){
for (int i=0; i <= 44; i++){
  if ((RRR+i)%22!=DNo-1){
  if ((RRR+i)/22==0 and No2_==Date_W((RRR+i)%22+1,tY)){Word_SSR=1;No3=(RRR+i)%22+1;break;}
  if ((RRR+i)/22!=0 and No2_==Date_W((RRR+i)%22+1,0)){Word_SSR=0;No3=(RRR+i)%22+1;break;}
  }  
}
  }else{
for (int i=0; i <= 22; i++){
  if ((RRR+i)%22!=DNo-1){
  if (Date_W((RRR+i)%22+1,tY)==1){Word_SSR=1;No3=(RRR+i)%22+1;break;}
  }
}
    }

  
  
  return No3;
  }

void setup() {
  // put your setup code here, to run once:

  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();
  tiyousi=random(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!arduboy.nextFrame()) return;
  arduboy.clear();
  
  arduboy.pollButtons();

KiriM=1;//きりたんの口
ZunM=1;//ずんだもんの口
MetaM=1;//めたんの口

Kiri_on=0;
Zun_on=0;
Meta_on=0;

TIME++;
//瞬き
  if (TIME==128){TIME=0;}
  KiriA=0;
  ZunA=0;
  MetaA=0;
  if ((TIME/3)%30==0){
    KiriA=1;
  }
  if ((TIME/3)%30==10){
    ZunA=1;
  }
  if ((TIME/3)%30==20){
    MetaA=1;
  }

Tk=0;
if (mode==0){//モード選択
  X_n=34;
  X2_n=-26;
  X3_n=85;
  Y=8;
  Tk=1;
  Tk_QC=0;
  if (arduboy.justPressed(LEFT_BUTTON) ){
      select_x=(select_x+2)%3;
  }
  
  if (arduboy.justPressed(RIGHT_BUTTON) ){
      select_x=(select_x+1)%3;
  }
  if (arduboy.justPressed(B_BUTTON)){
      mode=1;
      select_M=(1+select_x);
  }
}else if (mode==1){//モード内の詳細設定
  if(select_M!=2){
  X_n=128;
  X2_n=-66;
  X3_n=128;
  Y=8;
  Tk_C=0;
  talk_turn=0;
  Word_No=random(22)+1;
  if (select_y!=2){
    Tk=2;  
    if (arduboy.justPressed(LEFT_BUTTON)){
       select_x=(select_x+2)%3;
    }else if (arduboy.justPressed(RIGHT_BUTTON)){
       select_x=(select_x+1)%3;
    }
  }else{
    Tk=3;
    if (arduboy.justPressed(LEFT_BUTTON) or arduboy.justPressed(RIGHT_BUTTON)){
      select_x=(select_x+1)%2;
    }
  }
  if (select_y==0){select_P1=0;}
  if (select_y==1){select_P2=0;}
  
  if (arduboy.justPressed(A_BUTTON)){
      select_x=0;
    if (select_y==0){
      select_y=0;
      mode=0;
    }else{
      select_y--;
    }
  }
  if (select_y==0 and arduboy.justPressed(B_BUTTON)){
    select_P1=select_x+1;
    select_y=1;
  }else if (select_y==1 and arduboy.justPressed(B_BUTTON)){
    if (select_M==3 or select_P1!=select_x+1){
      select_P2=select_x+1;
      select_y=2;
      select_x=0;
    }
  }else if (select_y==2 and arduboy.justPressed(B_BUTTON)){
      if (select_x==0){
        mode=1+select_M;
      }else{
      select_y=1;  
      }
  }
  if (select_P1==1 and (select_P2==0 or select_P2==1)){
    X_n=36;
  } else if (select_P1==2 and (select_P2==0 or select_P2==2)){
    X3_n=38;
  } else if (select_P1==3 and (select_P2==0 or select_P2==3)){
    X2_n=27;
  }else if (select_P1!=0 and select_P2!=0){
    if (select_P1==2 or select_P2==2){
      X3_n=62;
      if (select_P1==1 or select_P2==1){
        X_n=1;
      }
    }
    if (select_P1==3 or select_P2==3){
      X2_n=1;
      if (select_P1==1 or select_P2==1){
        X_n=71;
      }
    }
  }
  }else{//クイズモード会話
    select_x=0;
    
  X_n=34;
  X2_n=-26;
  X3_n=85;
  
  if (Tk_QC>6){
  X_n=128;
  X2_n=-66;
  X3_n=128;
    if (Q_End==0){ X_n=36;}
    if (Q_End==1){X3_n=38;}
    if (Q_End==2){X2_n=27;}
  }
    Tk=4;
    if (Tk_QC<=0){Tk_QC=1;Q_Ten=0;Q_End=random(3);}
  if (arduboy.justPressed(B_BUTTON)){

  
    if (mes_time<=240){
      mes_time=238;
      }else{
        mes_time=0;
        Tk_QC++;
        if (Tk_QC==6){mode=3;Tk=4;}
        if (Tk_QC==15){mode=0;Tk_QC=0;}
      }
    } 
  if (mes_time<=240){
    mes_time=mes_time+2;
  }
  if (mes_PM==true){
  if (Tk_QC<=6){
    if (Tk_QC%3==1){ZunM=0;}
    if (Tk_QC%3==2){KiriM=0;}
    if (Tk_QC%3==0){MetaM=0;}
    }else{
    if (Q_End==2){ZunM=0;}
    if (Q_End==0){KiriM=0;}
    if (Q_End==1){MetaM=0;}
    }
  }
  mes_PM=false;

  if ((Tk_QC==2)and(mes_time<=2)){
  for (int i=0; i <= 22; i++){
    Q_dateM[i]=i+1;
    }
    
  for (int i=0; i <= 100; i++){
    RR=random(22);RRRR=random(22);
    Q_keep=Q_dateM[RR];
    Q_dateM[RR]=Q_dateM[RRRR];
    Q_dateM[RRRR]=Q_keep;
    }
    
    for (int i=0; i <= 21; i++){
      Q_date[i]=Q_dateM[i];
    }
    
    for (int i=0; i <= 7; i++){
      Q_Z[i]=random(3);
      Q_H[i]=random(4);
      Q_HZ[i]=random(3);
      
    }
  }

  }


  
}else if (mode==4){//フリーモード
  Y=0;
  if (arduboy.justPressed(LEFT_BUTTON)){
   select_x=0; 
  }
  if (arduboy.justPressed(RIGHT_BUTTON)){
   select_x=1; 
  }
  
  if (select_P1==1 and (select_P2==0 or select_P2==1)){
    Kiri_on=1;
  } else if (select_P1==2 and (select_P2==0 or select_P2==2)){
    Meta_on=1;
  } else if (select_P1==3 and (select_P2==0 or select_P2==3)){
    Zun_on=1;
  }else if (select_P1!=0 and select_P2!=0){
    if (select_P1==2 or select_P2==2){
        if (select_x==1){Meta_on=1;}
      if (select_P1==1 or select_P2==1){
        if (select_x==0){Kiri_on=1;}
      }
    }
    if (select_P1==3 or select_P2==3){
        if (select_x==0){Zun_on=1;}
      if (select_P1==1 or select_P2==1){
        if (select_x==1){Kiri_on=1;}
      }
    }
  }
  if (arduboy.pressed(B_BUTTON)){
    KiriM=1-Kiri_on;//きりたんの口
    ZunM=1-Zun_on;//ずんだもんの口
    MetaM=1-Meta_on;//めたんの口
  }
  if (arduboy.pressed(A_BUTTON) and (TIME%16)/8==0){
    KiriM=1-Kiri_on;//きりたんの口
    ZunM=1-Zun_on;//ずんだもんの口
    MetaM=1-Meta_on;//めたんの口
  }
  if (arduboy.pressed(UP_BUTTON)){
    KiriA=1*Kiri_on;//きりたんの目
    ZunA=1*Zun_on;//ずんだもんの目
    MetaA=1*Meta_on;//めたんの目
  }
  if (arduboy.pressed(DOWN_BUTTON)){
    KiriA=2*Kiri_on;//きりたんの目
    ZunA=2*Zun_on;//ずんだもんの目
    MetaA=2*Meta_on;//めたんの目
  }
  if ((arduboy.pressed(A_BUTTON))and(arduboy.pressed(B_BUTTON))){
    Back_C=Back_C+1;
      if (Back_C>=20){mode=1;}
  }else{Back_C=0;}

  
}else if (mode==2){//トークモード
  Y=8;
  Tk=4;
  
  if (arduboy.justPressed(A_BUTTON)){
    if (Tk_C<7){
    mode=1;
    mes_time=0;
    }
    //PROGMEM const uint8_t mesEndK1[] =
  }
  if (arduboy.pressed(A_BUTTON)){
    if ((Tk_C>=7)and(KAIZ<=5)){Back_C=Back_C+1;
      if (Back_C>=20){mes_time=0;KAIZ=10;KAI=16;}
    }
    //PROGMEM const uint8_t mesEndK1[] =
  }else{Back_C=0;}
  
  if (arduboy.justPressed(B_BUTTON)){
    if (mes_time<=240){
      mes_time=238;
      }else{
        mes_time=0;
        Tk_C++;
        talk_turn=(talk_turn+Tk_P)%2;
      }
    
  }
  if (mes_time<=240){
    mes_time=mes_time+2;
  }
  if (mes_PM==true){
    if (talk_turn==0){
    if (select_P1==1){
      KiriM=0;
    }else if (select_P1==2){
      MetaM=0;
    }else if (select_P1==3){
      ZunM=0;
    }
    }
    if (talk_turn==1){
    if (select_P2==1){
      KiriM=0;
    }else if (select_P2==2){
      MetaM=0;
    }else if (select_P2==3){
      ZunM=0;
    }
    }
  }
  mes_PM=false;
  if (Tk_C>=7 and mes_time==2){
  RR=random(2);
  if (KAIZ==2 or (KAIZ==3 and RR==1)){
  KAI=0;Word_No=random(22)+1;Word_SSR=random(2);
  }else if (KAIZ==0 or KAIZ==5){ 
  if (Word_SSR==0){KAI=1;Word_K=Date_W(Word_No,0);}
  if (Word_SSR!=0){
  if (Date_W(Word_No,select_P1)==Date_W(Word_No,select_P2)){KAI=1;}
  if (Date_W(Word_No,select_P1)!=Date_W(Word_No,select_P2)){KAI=2;}
  if (talk_turn==0){Word_K=Date_W(Word_No,select_P1);}
  if (talk_turn==1){Word_K=Date_W(Word_No,select_P2);}
  }
  }else if (KAIZ==1){
  KAI=3;
 
  if (talk_turn==0){ Word_1=Date_W(Word_No,select_P2);date_No=Word_S(Word_No,select_P1,Word_K);}
  if (talk_turn==1){ Word_1=Date_W(Word_No,select_P1);date_No=Word_S(Word_No,select_P2,Word_K);}
  Word_No=date_No;
  //gosub *SARCH
  //Word_No=No3;
  }else if (KAIZ==3 and RR==0){
  KAI=5;
  Word_SSR=(Word_SSR+1)%2;
  }else if (KAIZ==16){
    KAI=17;
  }else if (KAIZ==17){
    KAI=18;
  }else if (KAIZ==18){
    //スタートに戻る
    mode=0;
    mes_time=0;
    select_y=0;
    select_x=0;
    Tk=0;
    Tk_C=0;
  }
  
  KAIZ=KAI;
  }
}else if (mode==3){//クイズモード
  Y=8;
  Tk=5;
  //Tk_QC

    if ((mes_PM==true)and(mes_time%60<40)and(mes_time<180)){
    if (((Q_HZ[Tk_QC-6]+mes_time/60)%3)==1){KiriM=0;}
    if (((Q_HZ[Tk_QC-6]+mes_time/60)%3)==0){ZunM=0;}
    if (((Q_HZ[Tk_QC-6]+mes_time/60)%3)==2){MetaM=0;}
    
    
    }
  mes_PM=false;
  if (arduboy.justPressed(A_BUTTON)){
    }
      if (arduboy.justPressed(B_BUTTON)){
        
      Q_A=(Q_A+1)%2;
      if (Q_A==0){
      if (select_x==(Q_Z[Tk_QC-6])%3){Q_Ten=Q_Ten+9+(Tk_QC%4)/3;if (mes_time<240){Q_Ten=Q_Ten+(240-mes_time)/60+2;}}
      Tk_QC++;
      mes_time=0;
      if (Tk_QC>=13){mode=1;}
      }
      }
    
  if ((arduboy.justPressed(LEFT_BUTTON) )and(Q_A==0)){
      select_x=(select_x+2)%3;
  }
  
  if ((arduboy.justPressed(RIGHT_BUTTON) )and(Q_A==0)){
      select_x=(select_x+1)%3;
  }
  
  if (mes_time<240){
    if (Q_A==0){
    mes_time=mes_time+2;
    }
  }

}
  
  

  //ardbitmap.drawCompressed(64 , 32, kiri, 1 , ALIGN_CENTER, 0); //画像表示

for (int L=0; L <= 8; L++){
if (X_n>X){X++;}
if (X_n<X){X--;}
if (X2_n>X2){X2++;}
if (X2_n<X2){X2--;}
if (X3_n>X3){X3++;}
if (X3_n<X3){X3--;}
}


arduboy.fillRect(0,0,128,64,1);
//きりたん
Sprites::drawExternalMask(0+X, 0-Y, kiri,kiri_mask, 0, 0);
if (KiriA==0){
  Sprites::drawOverwrite(17+X, 27-Y, kiriAiL, 0);
  Sprites::drawOverwrite(33+X, 28-Y, kiriAiR, 0);
}else if (KiriA==1){
  Sprites::drawOverwrite(17+X, 29-Y, kiriAiT, 0);
  Sprites::drawOverwrite(33+X, 30-Y, kiriAiT, 0);
}else {
  Sprites::drawExternalMask(18+X, 27-Y, maru1,maru1_mask, 0, 0);
  Sprites::drawExternalMask(32+X, 28-Y, maru1,maru1_mask, 0, 0);
}
Sprites::drawOverwrite(25+X, 37-Y, kiriM1, 0);
  if (KiriM==1) {
Sprites::drawOverwrite(25+X, 37-Y, kiriM2, 0);
    } 

//ずんだもん
ZunMimi=0;
Sprites::drawExternalMask(7+X2, 8-Y, zun,zun_mask, 0, 0);
if (ZunA==0){
  Sprites::drawOverwrite(26+X2, 28-Y, zun_ai_L, 0);
  Sprites::drawOverwrite(38+X2, 27-Y, zun_ai_R, 0);
}else if (ZunA==1){
  Sprites::drawOverwrite(26+X2, 28-Y, zun_ai_L2, 0);
  Sprites::drawOverwrite(38+X2, 27-Y, zun_ai_R2, 0);
}else {
  Sprites::drawExternalMask(26+X2, 28-Y, maru1,maru1_mask, 0, 0);
  Sprites::drawExternalMask(39+X2, 27-Y, maru2,maru2_mask, 0, 0);
}
Sprites::drawOverwrite(33+X2, 35-Y, zun_M, 0);
  if (ZunM==1) {
    ZunMimi=1;
Sprites::drawOverwrite(33+X2, 35-Y, zun_M2, 0);
    } 

if (ZunMimi==0){
Sprites::drawExternalMask(3+X2, 0-Y, zun_mimi_L,zun_mimi_L_mask, 0, 0);
Sprites::drawExternalMask(43+X2, 0-Y, zun_mimi_R,zun_mimi_R_mask, 0, 0);
}else{
Sprites::drawExternalMask(0+X2, 12-Y, zun_mimi_L2,zun_mimi_L2_mask, 0, 0);
Sprites::drawExternalMask(43+X2, 8-Y, zun_mimi_R2,zun_mimi_R2_mask, 0, 0);
}

//めたん
Sprites::drawExternalMask(0+X3, 0-Y, metan,metan_mask, 0, 0);
if (MetaA==0){
  Sprites::drawOverwrite(21+X3, 27-Y, metan_ai_L, 0);
  Sprites::drawOverwrite(36+X3, 28-Y, metan_ai_R, 0);
}else if (MetaA==1){
  Sprites::drawOverwrite(21+X3, 27-Y, metan_ai_L2, 0);
  Sprites::drawOverwrite(36+X3, 28-Y, metan_ai_R2, 0);
}else {
  Sprites::drawExternalMask(35+X3, 28-Y, maru1,maru1_mask, 0, 0);
  Sprites::drawExternalMask(22+X3, 27-Y, maru2,maru2_mask, 0, 0);
}
  Sprites::drawOverwrite(28+X3, 36-Y, metan_M, 0);
    if (MetaM==1) {
  Sprites::drawOverwrite(28+X3, 36-Y, metan_M2, 0);
    }

if (Tk!=0){
  arduboy.fillRect(0,48,128,16,0);
  }
  if (Tk==1){
  drawText(0, 48, mesMode, sizeof(mesMode),WHITE);
  drawText(88, 56, mesFree2, sizeof(mesFree2),WHITE);
  drawText(8, 56, mesTalk2, sizeof(mesTalk2),WHITE);
  drawText(48, 56, mesQ, sizeof(mesQ),WHITE);
  drawText(0+40*select_x, 56, mesMigi, sizeof(mesMigi),WHITE);
  }else if (Tk==2){
  drawText(0, 48, mesDare, sizeof(mesDare),WHITE);
  if (select_P1!=1){drawText(8, 56, mesKiri, sizeof(mesKiri),WHITE);}
  if (select_P1!=2){drawText(48, 56, mesMeta, sizeof(mesMeta),WHITE);}
  if (select_P1!=3){drawText(88, 56, mesZun, sizeof(mesZun),WHITE);}
  if (select_P1!=0 and select_M==3){
    drawText(8+40*(select_P1-1), 56, mes1Dake, sizeof(mes1Dake),WHITE);
  }
  arduboy.fillRect(0+40*select_x,56,8,8,0);
  drawText(0+40*select_x, 56, mesMigi, sizeof(mesMigi),WHITE);
  }else if (Tk==3){
  
  drawText(0, 48, mesKorede, sizeof(mesKorede),WHITE);
  drawText(8, 56, mesHai, sizeof(mesHai),WHITE);
  drawText(72, 56, mesTiga, sizeof(mesTiga),WHITE);
  drawText(0+64*select_x, 56, mesMigi, sizeof(mesMigi),WHITE);
  }else if (Tk==4){//トークモード内容
  arduboy.fillRect(0,48,16,8,1);
  if ((talk_turn==0)and(Tk_QC==0)){
  if (select_P1==1){
  drawText(0, 48, mesKiriN, sizeof(mesKiriN),BLACK);
  }else if (select_P1==2){
  drawText(0, 48, mesMetaN, sizeof(mesMetaN),BLACK);
  }else if (select_P1==3){
  drawText(0, 48, mesZunN, sizeof(mesZunN),BLACK);
  }
  }
  if((talk_turn==1)and(Tk_QC==0)){
  if (select_P2==1){
  drawText(0, 48, mesKiriN, sizeof(mesKiriN),BLACK);
  }else if (select_P2==2){
  drawText(0, 48, mesMetaN, sizeof(mesMetaN),BLACK);
  }else if (select_P2==3){
  drawText(0, 48, mesZunN, sizeof(mesZunN),BLACK);
  }
  }


  if (Tk_QC==1){//クイズ用
  drawText(0, 48, mesZunN, sizeof(mesZunN),BLACK);
  drawText(16, 48, mesQQ1, sizeof(mesQQ1),WHITE);
  }
  if (Tk_QC==2){
  drawText(0, 48, mesKiriN, sizeof(mesKiriN),BLACK);
  drawText(16, 48, mesQQ2, sizeof(mesQQ2),WHITE);
  }
  if (Tk_QC==3){
  drawText(0, 48, mesMetaN, sizeof(mesMetaN),BLACK);
  drawText(16, 48, mesQQ3, sizeof(mesQQ3),WHITE);
  }
  if (Tk_QC==4){
  drawText(0, 48, mesZunN, sizeof(mesZunN),BLACK);
  drawText(16, 48, mesQQ4, sizeof(mesQQ4),WHITE);
  }
  if (Tk_QC==5){
  drawText(0, 48, mesKiriN, sizeof(mesKiriN),BLACK);
  drawText(16, 48, mesQQ5, sizeof(mesQQ5),WHITE);
  }
  if (Tk_QC==13){
  if (Q_End==0){
    drawText(0, 48, mesKiriN, sizeof(mesKiriN),BLACK);
    drawText(16, 48, mesQ_end_K_1, sizeof(mesQ_end_K_1),WHITE);
    drawText(0, 56, mesQ_end_K_2, sizeof(mesQ_end_K_2),WHITE);
  }
  if (Q_End==1){
    drawText(0, 48, mesMetaN, sizeof(mesMetaN),BLACK);
    drawText(16, 48, mesQ_end_M_1, sizeof(mesQ_end_M_1),WHITE);
    drawText(0, 56, mesQ_end_M_2, sizeof(mesQ_end_M_2),WHITE);
  }
  if (Q_End==2){
    drawText(0, 48, mesZunN, sizeof(mesZunN),BLACK);
    drawText(16, 48, mesQ_end_Z_1, sizeof(mesQ_end_Z_1),WHITE);
    drawText(0, 56, mesQ_end_Z_2, sizeof(mesQ_end_Z_2),WHITE);
  }
  arduboy.setCursor(73,56);
  if (Q_Ten/100>0){arduboy.print(Q_Ten/100);}
  arduboy.setCursor(81,56);
  if (Q_Ten/10>0){arduboy.print(Q_Ten%100/10);}
  arduboy.setCursor(89,56);
  arduboy.print(Q_Ten%10);
  }
  if (Tk_QC==14){
  
  if (Q_End==0){
  drawText(0, 48, mesKiriN, sizeof(mesKiriN),BLACK);
  if (Q_Ten>85){drawText(16, 48, mesQ_end_K_3, sizeof(mesQ_end_K_3),WHITE);}
  if ((Q_Ten<=85)and(Q_Ten>70)){drawText(16, 48, mesQ_end_K_4, sizeof(mesQ_end_K_4),WHITE);}
  if ((Q_Ten<=70)and(Q_Ten>50)){drawText(16, 48, mesQ_end_K_5, sizeof(mesQ_end_K_5),WHITE);}
  if ((Q_Ten<=50)and(Q_Ten>20)){drawText(16, 48, mesQ_end_K_6, sizeof(mesQ_end_K_6),WHITE);}
  if (Q_Ten<=20){drawText(16, 48, mesQ_end_K_7, sizeof(mesQ_end_K_7),WHITE);}
  }
  if (Q_End==1){
  drawText(0, 48, mesMetaN, sizeof(mesMetaN),BLACK);
  if (Q_Ten>85){drawText(16, 48, mesQ_end_M_3, sizeof(mesQ_end_M_3),WHITE);}
  if ((Q_Ten<=85)and(Q_Ten>70)){drawText(16, 48, mesQ_end_M_4, sizeof(mesQ_end_M_4),WHITE);}
  if ((Q_Ten<=70)and(Q_Ten>50)){drawText(16, 48, mesQ_end_M_5, sizeof(mesQ_end_M_5),WHITE);}
  if ((Q_Ten<=50)and(Q_Ten>20)){drawText(16, 48, mesQ_end_M_6, sizeof(mesQ_end_M_6),WHITE);}
  if (Q_Ten<=20){drawText(16, 48, mesQ_end_M_7, sizeof(mesQ_end_M_7),WHITE);}
  }
  if (Q_End==2){
  drawText(0, 48, mesZunN, sizeof(mesZunN),BLACK);
  if (Q_Ten>85){drawText(16, 48, mesQ_end_Z_3, sizeof(mesQ_end_Z_3),WHITE);}
  if ((Q_Ten<=85)and(Q_Ten>70)){drawText(16, 48, mesQ_end_Z_4, sizeof(mesQ_end_Z_4),WHITE);}
  if ((Q_Ten<=70)and(Q_Ten>50)){drawText(16, 48, mesQ_end_Z_5, sizeof(mesQ_end_Z_5),WHITE);}
  if ((Q_Ten<=50)and(Q_Ten>20)){drawText(16, 48, mesQ_end_Z_6, sizeof(mesQ_end_Z_6),WHITE);}
  if (Q_Ten<=20){drawText(16, 48, mesQ_end_Z_7, sizeof(mesQ_end_Z_7),WHITE);}
  }


  
  }
  
  
  Tk_P=0;
  if ((Tk_C==0)and(Tk_QC==0)){//他
  Tk_P=1;
  if (select_P1==1){
  drawText(16, 48, mesTest1, sizeof(mesTest1),WHITE);
  }else if (select_P1==2){
  drawText(16, 48, mesTest2, sizeof(mesTest2),WHITE);
  }else if (select_P1==3){
  drawText(16, 48, mesTest3, sizeof(mesTest3),WHITE);
  }
  
  }
  if (Tk_C==1){
  if (select_P2==1){
  drawText(16, 48, mesHi, sizeof(mesHi),WHITE);
  }else if (select_P2==2){
  drawText(16, 48, mesHi, sizeof(mesHi),WHITE);
  }else if (select_P2==3){
  drawText(16, 48, mesHiN, sizeof(mesHiN),WHITE);
  }
  if (select_P1==1){
  drawText(88-(select_P2!=3)*24, 48, mesKiri, sizeof(mesKiri),WHITE);
  }else if (select_P1==2  and select_P2 != 1){
  drawText(88-(select_P2!=3)*24, 48, mesMeta, sizeof(mesMeta),WHITE);
  }else if (select_P1==2  and select_P2 == 1){
  drawText(88-(select_P2!=3)*24, 48, mesMeta2, sizeof(mesMeta2),WHITE);
  }else if (select_P1==3){
  drawText(88-(select_P2!=3)*24, 48, mesZun, sizeof(mesZun),WHITE);
  }
  }

  if (Tk_C==2){
    Tk_P=1;
  if (select_P1==1){
  drawText(16, 48, mesKiri, sizeof(mesKiri),WHITE);
  }else if (select_P1==2  and select_P2 != 1){
  drawText(16, 48, mesMeta, sizeof(mesMeta),WHITE);
  }else if (select_P1==2  and select_P2 == 1){
  drawText(16, 48, mesMeta2, sizeof(mesMeta2),WHITE);
  }else if (select_P1==3){
  drawText(16, 48, mesZun, sizeof(mesZun),WHITE);
  }
  drawText(56, 48, mesSaikin, sizeof(mesSaikin),WHITE);
  
  if (select_P2==1){
  drawText(24, 56, mesDesuka, sizeof(mesDesuka),WHITE);
  }else if (select_P2==2){
  drawText(24, 56, mesKasira, sizeof(mesKasira),WHITE);
  }else if (select_P2==3){
  drawText(24, 56, mesNanodaH, sizeof(mesNanodaH),WHITE);
  }
  }

  if (Tk_C==3){
  if ((select_P1+tiyousi)%3==0){
  drawText(16, 48, mesMama, sizeof(mesMama),WHITE);
  }else if ((select_P1+tiyousi)%3==1){
  drawText(16, 48, mesBoti, sizeof(mesBoti),WHITE);
  }else if ((select_P1+tiyousi)%3==2){
  drawText(16, 48, mesGenki, sizeof(mesGenki),WHITE);
  }
  if (select_P1==1){
  drawText(48, 48, mesDesu, sizeof(mesDesu),WHITE);
  }else if (select_P1==2){
  drawText(48, 48, mesYo, sizeof(mesYo),WHITE);
  }else if (select_P1==3){
  drawText(48, 48, mesNanodaB, sizeof(mesNanodaB),WHITE);
  }
  }

  if (Tk_C==4){
    Tk_P=1;
  if (select_P1==1){
  drawText(16, 48, mesQA1, sizeof(mesQA1),WHITE);
  }else if (select_P1==2){
  drawText(16, 48, mesQA2, sizeof(mesQA2),WHITE);
  }else if (select_P1==3){
  drawText(16, 48, mesQA3, sizeof(mesQA3),WHITE);
  }
  }

  if (Tk_C==5){
    Tk_P=1;
  if (select_P2==1){
  drawText(16, 48, mesQAA1, sizeof(mesQAA1),WHITE);
  }else if (select_P2==2){
  drawText(16, 48, mesQAA2, sizeof(mesQAA2),WHITE);
  }else if (select_P2==3){
  drawText(16, 48, mesQAA3, sizeof(mesQAA3),WHITE);
  }
  }
  
  if (Tk_C==6){
    Tk_P=1;
    KAI=0;
    KAIZ=7;
  if (select_P2==1){
  drawText(16, 48, mesKiri, sizeof(mesKiri),WHITE);
  }else if (select_P2==2  and select_P1 != 1){
  drawText(16, 48, mesMeta, sizeof(mesMeta),WHITE);
  }else if (select_P2==2  and select_P1 == 1){
  drawText(16, 48, mesMeta2, sizeof(mesMeta2),WHITE);
  }else if (select_P2==3){
  drawText(16, 48, mesZun, sizeof(mesZun),WHITE);
  }
  drawText(56, 48, mesWa, sizeof(mesWa),WHITE);
  
  Word_Draw(8, Word_No,0);
  drawText(104, 48, mesTe, sizeof(mesTe),WHITE);
  drawText(120, 48, mesDou, sizeof(mesDou),WHITE);
  if (select_P1==1){
  drawText(48, 56, mesSuka1, sizeof(mesSuka1),WHITE);
  }else if (select_P1==2){
  drawText(48, 56, mesSuka2, sizeof(mesSuka2),WHITE);
  }else if (select_P1==3){
  drawText(48, 56, mesSuka3, sizeof(mesSuka3),WHITE);
  }
  }
  if (Tk_C>=7){
    if (Word_SSR==0){Word_SSR2=0;}
    if (Word_SSR!=0 and talk_turn==0){Word_SSR2=select_P1;}
    if (Word_SSR!=0 and talk_turn==1){Word_SSR2=select_P2;}


  arduboy.setCursor(40,0);
  //arduboy.print(Word_No);
  //Word_1=Date_W(Word_No,0);
  arduboy.setCursor(64,0);
  //arduboy.print(Word_1);
  
  talk_Pt=0;
  if (((select_P2==1)and(talk_turn==1))or((select_P1==1)and(talk_turn==0))){talk_Pt=1;}
  if (((select_P2==2)and(talk_turn==1))or((select_P1==2)and(talk_turn==0))){talk_Pt=2;}
  if (((select_P2==3)and(talk_turn==1))or((select_P1==3)and(talk_turn==0))){talk_Pt=3;}

    
    if (KAI==0){
      if (talk_Pt<=1){
      Word_Draw(2, Word_No,0);
      drawText(56, 48, mesTe, sizeof(mesTe),WHITE);
      Word_Draw(9, Date_W(Word_No,Word_SSR2),1);
      drawText(112, 48, mesDesuyone, sizeof(mesDesuyone),WHITE);
    Tk_P=1;
      }
      if (talk_Pt==2){
      Word_Draw(2, Word_No,0);
      drawText(56, 48, mesTe, sizeof(mesTe),WHITE);
      Word_Draw(9, Date_W(Word_No,Word_SSR2),1);
      drawText(112, 48, mesYone, sizeof(mesYone),WHITE);
    Tk_P=1;
      }
      if (talk_Pt==3){
      Word_Draw(2, Word_No,0);
      drawText(56, 48, mesTe, sizeof(mesTe),WHITE);
      Word_Draw(9, Date_W(Word_No,Word_SSR2),1);
      drawText(112, 48, mesNanodaB, sizeof(mesNanodaB),WHITE);
    Tk_P=1;
      }

  
      
      }
      
    if (KAI==1){
      if (talk_Pt<=1){
      drawText(16, 48, mesSouKoutei1, sizeof(mesSouKoutei1),WHITE);
      }
      if (talk_Pt==2){
      drawText(16, 48, mesSouKoutei12, sizeof(mesSouKoutei12),WHITE);
      }
      if (talk_Pt==3){
      drawText(16, 48, mesSouKoutei13, sizeof(mesSouKoutei13),WHITE);
      }
      //Date_W(Word_No,Word_SSR2)
      }
    if (KAI==2){
      if (talk_Pt<=1){
      drawText(16, 48, mesSouWatasi1, sizeof(mesSouWatasi1),WHITE);
      Word_Draw(12, Date_W(Word_No,Word_SSR2),1);
      drawText(8, 56, mesOmoimasu1, sizeof(mesOmoimasu1),WHITE);
    Tk_P=1;
      }
      if (talk_Pt==2){
      drawText(16, 48, mesSouWatasi12, sizeof(mesSouWatasi12),WHITE);
      Word_Draw(8, Date_W(Word_No,Word_SSR2),1);
      drawText(104, 48, mesOmoimasu12, sizeof(mesOmoimasu12),WHITE);
    Tk_P=1;
      }
      if (talk_Pt==3){
      drawText(16, 48, mesSouWatasi13, sizeof(mesSouWatasi13),WHITE);
      Word_Draw(12, Date_W(Word_No,Word_SSR2),1);
      drawText(0, 56, mesNanodaB, sizeof(mesNanodaB),WHITE);
    Tk_P=1;
      }
      
      }
    if (KAI==3){
      if (talk_Pt<=1){
      Word_Draw(2,  Word_K,1);
      drawText(56, 48, mesTeIeba, sizeof(mesTeIeba),WHITE);
      Word_Draw(12, Word_No,0);
      drawText(8, 56, mesMosou, sizeof(mesMosou),WHITE);
      }
      if (talk_Pt==2){
      Word_Draw(2,  Word_K,1);
      drawText(56, 48, mesTeIeba, sizeof(mesTeIeba),WHITE);
      Word_Draw(12, Word_No,0);
      drawText(8, 56, mesMosou2, sizeof(mesMosou2),WHITE);
      }
      if (talk_Pt==3){
      Word_Draw(2,  Word_K,1);
      drawText(56, 48, mesTeIeba, sizeof(mesTeIeba),WHITE);
      Word_Draw(12, Word_No,0);
      drawText(8, 56, mesMosou3, sizeof(mesMosou3),WHITE);
      }
      
      }
    if (KAI==5){
      if (talk_Pt<=1){
      drawText(16, 48, mesSouie, sizeof(mesSouie),WHITE);
      Word_Draw(7, Date_W(Word_No,Word_SSR2),1);
      drawText(96, 48, mesTe, sizeof(mesTe),WHITE);
      Word_Draw(14, Word_No,0);
      drawText(24, 56, mesMoari, sizeof(mesMoari),WHITE);
    Tk_P=1;
      }
      if (talk_Pt==2){
      drawText(16, 48, mesSouie, sizeof(mesSouie),WHITE);
      Word_Draw(7, Date_W(Word_No,Word_SSR2),1);
      drawText(96, 48, mesTe, sizeof(mesTe),WHITE);
      Word_Draw(14, Word_No,0);
      drawText(24, 56, mesMoari2, sizeof(mesMoari2),WHITE);
    Tk_P=1;
      }
      if (talk_Pt==3){
      drawText(16, 48, mesSouie, sizeof(mesSouie),WHITE);
      Word_Draw(7, Date_W(Word_No,Word_SSR2),1);
      drawText(96, 48, mesTe, sizeof(mesTe),WHITE);
      Word_Draw(14, Word_No,0);
      drawText(24, 56, mesMoari3, sizeof(mesMoari3),WHITE);
    Tk_P=1;
      }

    }
      if (KAI==16){
      if (talk_Pt<=1){
      drawText(16, 48, mesEndK1, sizeof(mesEndK1),WHITE);
      }
      if (talk_Pt==2){
      drawText(16, 48, mesEndM1, sizeof(mesEndM1),WHITE);
      }
      if (talk_Pt==3){
      drawText(16, 48, mesEndZ1, sizeof(mesEndZ1),WHITE);
      }
     Tk_P=1;
      }
      if (KAI==17){
      if (talk_Pt<=1){
      drawText(16, 48, mesEndK2, sizeof(mesEndK2),WHITE);
      }
      if (talk_Pt==2){
      drawText(16, 48, mesEndM2, sizeof(mesEndM2),WHITE);
      }
      if (talk_Pt==3){
      drawText(16, 48, mesEndZ2, sizeof(mesEndZ2),WHITE);
      }
     Tk_P=1;
      }
      if (KAI==18){
      if (talk_Pt<=1){
      drawText(16, 48, mesEndK3, sizeof(mesEndK3),WHITE);
      }
      if (talk_Pt==2){
      drawText(16, 48, mesEndM3, sizeof(mesEndM3),WHITE);
      }
      if (talk_Pt==3){
      drawText(16, 48, mesEndZ3, sizeof(mesEndZ3),WHITE);
      }
     Tk_P=1;
      }
  
  }


  
  if (mes_time<112){
    arduboy.fillRect(24+mes_time/8*8,48,112,8,0);
    arduboy.fillRect(0,56,128,8,0);
    if (Arduboy2Base::getPixel(15+mes_time,49)){mes_PM=true;}
    
  }else if (mes_time>=112){
    arduboy.fillRect(mes_time/8*8-112+8,56,128,8,0);
    if (Arduboy2Base::getPixel(mes_time-112,57)){mes_PM=true;}
  }
  
  //      arduboy.setCursor(64, 56);
  //      arduboy.print(Arduboy2Base::getPixel(15+mes_time,50));
  //if (Arduboy2Base::getPixel(15+mes_time,50)){mes_PM=true;}

  
  }else if (Tk==5){
  QQQ=(Tk_QC-6)*3;
  //if (Tk_QC==6){
  if (Tk_QC!=6){
  if (Q_H[(QQQ+1)/3]!=2){Word_Draw(1, Date_W(Q_date[QQQ],3),1);}else{Word_Draw(1, Date_W(Q_date[QQQ],0),1);}
  if (Q_H[(QQQ+1)/3]!=0){Word_Draw(6, Date_W(Q_date[QQQ],1),1);}else{Word_Draw(6, Date_W(Q_date[QQQ],0),1);}
  if (Q_H[(QQQ+1)/3]!=1){Word_Draw(11, Date_W(Q_date[QQQ],2),1);}else{Word_Draw(11, Date_W(Q_date[QQQ],0),1);}
    Word_Draw(17+((Q_Z[(QQQ+1)/3])%3)*5, Q_date[QQQ],0);
  }
    Word_Draw(17+((Q_Z[(QQQ+1)/3]+1)%3)*5, Q_date[QQQ+1],0);
    Word_Draw(17+((Q_Z[(QQQ+1)/3]+2)%3)*5, Q_date[QQQ+2],0);
  //}
  if (Tk_QC==6){
  //Word_Draw(1, Date_W(50,3),1);
  //Word_Draw(6, Date_W(50,1),1);
  //Word_Draw(11, Date_W(50,2),1);
    //Word_Draw(17+((Q_Z[0])%3)*5, 50,0);
    if (Q_H[0]!=2){Word_Draw(1, Date_W(Q_dateM[21],3),1);}else{Word_Draw(1, Date_W(Q_dateM[21],0),1);}
    if (Q_H[0]!=0){Word_Draw(6, Date_W(Q_dateM[21],1),1);}else{Word_Draw(6, Date_W(Q_dateM[21],0),1);}
    if (Q_H[0]!=1){Word_Draw(11, Date_W(Q_dateM[21],2),1);}else{Word_Draw(11, Date_W(Q_dateM[21],0),1);}
  
    Word_Draw(17+((Q_Z[0])%3)*5, Q_dateM[21],0);
    
  }

  //Q_HZ
  
  if (Arduboy2Base::getPixel((8+40*((Q_HZ[(QQQ+1)/3])%3)+mes_time)%128,49)){mes_PM=true;}
  if (Q_A==1){arduboy.fillRect(8+40*((Q_Z[(QQQ+1)/3])%3), 56,39, 7, 0);drawText(16+40*((Q_Z[(QQQ+1)/3])%3), 56, mesMaru, sizeof(mesMaru),WHITE);}
  if ((Q_A==1) and (((Q_Z[(QQQ+1)/3])%3)!=select_x)){arduboy.fillRect(8+40*select_x, 56,39, 7, 0);drawText(16+40*select_x, 56, mesBatu, sizeof(mesBatu),WHITE);}
  if ((mes_time/60==0)and(mes_time<40)){arduboy.fillRect(8+40*((Q_HZ[(QQQ+1)/3])%3)+mes_time/8*8, 48,40-mes_time/8*8, 7, 0);}
  if (mes_time/60==0){arduboy.fillRect(8+40*((Q_HZ[(QQQ+1)/3]+1)%3)+0, 48,40, 7, 0);}
  if ((mes_time/60==1)and(mes_time-60<40)){arduboy.fillRect(8+40*((Q_HZ[(QQQ+1)/3]+1)%3)+(mes_time-60)/8*8, 48,40-(mes_time-60)/8*8, 7, 0);}
  if ((mes_time/60==0)or(mes_time/60==1)){arduboy.fillRect(8+40*((Q_HZ[(QQQ+1)/3]+2)%3)+0, 48,40, 7, 0);}
  if ((mes_time/60==2)and(mes_time-120<40)){arduboy.fillRect(8+40*((Q_HZ[(QQQ+1)/3]+2)%3)+(mes_time-120)/8*8, 48,40-(mes_time-120)/8*8, 7, 0);}
    arduboy.fillRect(0+40*select_x, 56,7, 7, 0);
  drawText(0+40*select_x, 56, mesMigi, sizeof(mesMigi),WHITE);
  arduboy.fillRect(mes_time*128/240, 44, 128-mes_time*128/240, 2, 0);


  
  arduboy.setCursor(0,0);
  arduboy.print(Q_Ten);
  arduboy.setCursor(122,0);
  arduboy.print(Tk_QC-5);
   
  }




  arduboy.display();
}
