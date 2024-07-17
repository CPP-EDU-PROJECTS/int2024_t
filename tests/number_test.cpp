#include <lib/number.h>
#include <gtest/gtest.h>
#include <tuple>
#include <cstring>

class ConvertingTestsSuite : public testing::TestWithParam<std::tuple<uint32_t, const char*, bool>> {
};

TEST_P(ConvertingTestsSuite, EqualTest) {
    int2024_t a = from_int(std::get<0>(GetParam()));
    int2024_t b = from_string(std::get<1>(GetParam()));

    if(std::get<2>(GetParam()))
        ASSERT_EQ(a,b) << std::get<0>(GetParam()) << " == " << std::get<1>(GetParam());
    else
        ASSERT_NE(a,b) << std::get<0>(GetParam()) << " != " << std::get<1>(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    Group,
    ConvertingTestsSuite,
    testing::Values(
        // positive
        std::make_tuple(0, "0", true),
        std::make_tuple(239,"239", true),
        std::make_tuple(255,"255", true),
        std::make_tuple(256,"256", true),
        std::make_tuple(10000,"10000", true),
        std::make_tuple(32767,"32767", true),
        std::make_tuple(32768,"32768", true),
        std::make_tuple(65535,"65535", true),
        std::make_tuple(2147483647,"2147483647", true),
        std::make_tuple(-32768,"-32768", true),
        std::make_tuple(-65535,"-65535", true),
        std::make_tuple(-2147483647,"-2147483647", true),

        // negative
        std::make_tuple(0, "1", false),
        std::make_tuple(32768,"32769", false),
        std::make_tuple(255,"256", false),
        std::make_tuple(256,"255", false),
        std::make_tuple(31251,"31252", false),
        std::make_tuple(2147483647,"2147483648", false),
        std::make_tuple(-32768,"32768", false),
        std::make_tuple(-65535,"65535", false),
        std::make_tuple(-2147483647,"2147483647", false),
        std::make_tuple(-2147483648,"2147483648", false)
    )
);


class OperationTestsSuite
    : public testing::TestWithParam<
        std::tuple<
            const char*, // lhs
            const char*, // rhs
            const char*, // +
            const char*, // -
            const char*, // *
            const char*  // /
        >
    > {
};

TEST_P(OperationTestsSuite, AddTest) {
    int2024_t a = from_string(std::get<0>(GetParam()));
    int2024_t b = from_string(std::get<1>(GetParam()));

    int2024_t result = a + b;
    int2024_t expected = from_string((std::get<2>(GetParam())));

    ASSERT_EQ(result, expected);
}

TEST_P(OperationTestsSuite, SubstTest) {
    int2024_t a = from_string(std::get<0>(GetParam()));
    int2024_t b = from_string(std::get<1>(GetParam()));

    int2024_t result = a - b;
    int2024_t expected = from_string((std::get<3>(GetParam())));

    ASSERT_EQ(result, expected);
}

TEST_P(OperationTestsSuite, MultTest) {
    int2024_t a = from_string(std::get<0>(GetParam()));
    int2024_t b = from_string(std::get<1>(GetParam()));

    int2024_t result = a * b;
    int2024_t expected = from_string((std::get<4>(GetParam())));

    ASSERT_EQ(result, expected);
}

TEST_P(OperationTestsSuite, DivTest) {
    int2024_t a = from_string(std::get<0>(GetParam()));
    int2024_t b = from_string(std::get<1>(GetParam()));

    if(strcmp(std::get<1>(GetParam()), "0")){

        int2024_t result = a / b;
        int2024_t expected = from_string((std::get<5>(GetParam())));

        ASSERT_EQ(result, expected);
    }
}

INSTANTIATE_TEST_SUITE_P(
    Group,
    OperationTestsSuite,
    testing::Values(
        std::make_tuple("1", "1", "2", "0", "1", "1"),
        std::make_tuple("1024", "1", "1025", "1023", "1024", "1024"),
        std::make_tuple("405272312330606683982498447530407677486444946329741970511324085183808429621437",
                        "1",
                        "405272312330606683982498447530407677486444946329741970511324085183808429621438",
                        "405272312330606683982498447530407677486444946329741970511324085183808429621436",
                        "405272312330606683982498447530407677486444946329741970511324085183808429621437",
                        "405272312330606683982498447530407677486444946329741970511324085183808429621437"
        ),
        std::make_tuple("405272312330606683982498447530407677486444946329741977764879002871583477858493",
                        "0",
                        "405272312330606683982498447530407677486444946329741977764879002871583477858493",
                        "405272312330606683982498447530407677486444946329741977764879002871583477858493",
                        "0",
                        "ignored"
        ),
        std::make_tuple(
            "405272312330606683982498447530407677486444946329741974138101544027695953739965",
            "3626777458843887524118528",
            "405272312330606683982498447530407677486444946329741977764879002871583477858493",
            "405272312330606683982498447530407677486444946329741970511324085183808429621437",
            "1469832487054184013178321496623041557517329857560238757278117847507488415462666081345922349701550571520",
            "111744466521471062588629470729710044638866394325887658"
        ),
        std::make_tuple(
                "-1282",
                "2530",
                "1248",
                "-3812",
                "-3243460",
                "0"
        ),
        std::make_tuple(
                "-3661",
                "-3614",
                "-7275",
                "-47",
                "13230854",
                "1"
        ),
        std::make_tuple(
                "-3896",
                "-1908",
                "-5804",
                "-1988",
                "7433568",
                "2"
        ),
        std::make_tuple(
                "-73989903274620946355896497534176567458423271806658992916116356604130779555503",
                "-96128587107354470568792418496253598745583634292863565170370785011992475364274",
                "-170118490381975416924688916030430166204006906099522558086487141616123254919777",
                "22138683832733524212895920962077031287160362486204572254254428407861695808771",
                "7112544861999131427278221601020599388013187742552628437053780586823271949128539661894241777511953875252963043273289810912019592919490136018016431726299822",
                "0"
        ),
        std::make_tuple(
                "-99221571607979123665780991349421372751072036634265333790224952842857143556818",
                "-65529078579099725249902581203152790807201440339173524296737345244458286237794",
                "-164750650187078848915683572552574163558273476973438858086962298087315429794612",
                "-33692493028879398415878410146268581943870596295091809493487607598398857319024",
                "6501898162641034274110853689515764769183761809588644470881322763147958693421930138013906548531873889642466048576162732984252589674467061280043488897979492",
                "1"
        ),
        std::make_tuple(
                "-36910543626357909786996858927504055915546565889432391444809017960754559034869",
                "-67532224128613087281662110248791958688454806792296727573054956633143475837222",
                "-104442767754970997068658969176296014604001372681729119017863974593898034872091",
                "30621680502255177494665251321287902772908240902864336128245938672388916802353",
                "2492651104884153636937631117191849081819453420865277715427945122948178546599917829034047583175092105714470305515561503981419101504708025332458254066093918",
                "0"
        ),
        std::make_tuple(
                "-88855163870341754842750315870614312116360574967963774070817708633119401939135",
                "-81563986793718630029735428226007353499088224879562093056794053617199222693159",
                "-170419150664060384872485744096621665615448799847525867127611762250318624632294",
                "-7291177076623124813014887644606958617272350088401681014023655015920179245976",
                "7247381412474259645444820598526678727333707943393369800154711784059232717074390446266342734896555800030626580833056297093044421952446372518824881698877465",
                "1"
        ),
        std::make_tuple(
                "-68849238462076040579623317176146477521262781110665354478170488330043650923186",
                "-71179774459146621954624263114204033447348272489955909646997340730319785986765",
                "-140029012921222662534247580290350510968611053600621264125167829060363436909951",
                "2330535997070581375000945938057555926085491379290555168826852400276135063579",
                "4900673265414575403283020931754806415526873161026348792632208277230756589879577463632166517022145872149325698962335940491526779458276425071774238227633290",
                "0"
        ),
        std::make_tuple(
                "-82525551859180769338356537095667899997940203894520739123078359239582931071496",
                "-70937068087195689802196086497885550869204550154344904328970246838414875130163",
                "-153462619946376459140552623593553450867144754048865643452048606077997806201659",
                "-11588483771985079536160450597782349128735653740175834794108112401168055941333",
                "5854120691168105079515485575721104885173654361210637047927063838942959569168266271189749455297711960080075388343560555696492171912349388159767960059133848",
                "1"
        ),
        std::make_tuple(
                "-77395514233945693851309379069318824882565188883653627192010699993199608317469",
                "-78577375039869595983650414228663617994836280624125539477368993945122062666954",
                "-155972889273815289834959793297982442877401469507779166669379693938321670984423",
                "1181860805923902132341035159344793112271091740471912285358293951922454349485",
                "6081536348364316398843811021653824372214471501524039541055122504868125757436386607408632696145953775441116959716063564228770585152105032580103466847219426",
                "0"
        ),
        std::make_tuple(
                "-67986512732075487315221040743176172402098301981074288624134434874570594916189",
                "-90492950813443436905120056393867146147609547163158939908057387970819739059922",
                "-158479463545518924220341097137043318549707849144233228532191822845390333976111",
                "22506438081367949589899015650690973745511245182084651283922953096249144143733",
                "6152300152641253049815119930066554513290532021180687776932537099849242375837358748670939302969937732683303314396295945434233018879573638306351043238877258",
                "0"
        ),
        std::make_tuple(
                "-76274280532169161947344894940665778832558853403881828514553163329962471884371",
                "-56845854057590252584006989429627957413326802230550090002766152423691466199867",
                "-133120134589759414531351884370293736245885655634431918517319315753653938084238",
                "-19428426474578909363337905511037821419232051173331738511787010906271005684504",
                "4335876619479385564872152673121822012587581207204663640736436486602325147544118417481026678820078226988641235142537430322987520845335143334540845999578657",
                "1"
        ),
        std::make_tuple(
                "-37524906559012625607594720163609851303954535263701568652191903636685120612512",
                "-55627717134782002331025974681758179291147628290118003381475391126414775855903",
                "-93152623693794627938620694845368030595102163553819572033667294763099896468415",
                "18102810575769376723431254518148327987193093026416434729283487489729655243391",
                "2087424887573880180034603735162620138823842432308768321585886938106965787533830899049366493156956540347184795825548164412753052246412858620271452410858336",
                "0"
        ),
        std::make_tuple(
                "-42344127027586150326858908364592447171456924859482671531491421249667097722632",
                "-64033119192930786369855153249687612316535508118289072695888014347370611057501",
                "-106377246220516936696714061614280059487992432977771744227379435597037708780133",
                "21688992165344636042996244885095165145078583258806401164396593097703513334869",
                "2711426533078025972208878631807204481081375401842072712309070662828337810862767172806879647248434143296200451776597497219281309337836828632494154301062632",
                "0"
        ),
        std::make_tuple(
                "-72871897469819293737367872833326987466367646586482254424286949504560031874005",
                "65670123909401983585308549786595851694410179714945696570320001142378944542562",
                "-7201773560417310152059323046731135771957466871536557853966948362181087331443",
                "-138542021379221277322676422619922839160777826301427950994606950646938976416567",
                "-4785506536356269914184970909892200885739030922927006064801915887034252297002241486295804408378222125039917160600543251489604663813119893925272964343900810",
                "-1"
        ),
        std::make_tuple(
                "-74740812139497906314119485815115358176873775528344185232088990644697244287674",
                "90973981485507717095129134252973816730599686062803809890530539978021004214092",
                "16233169346009810781009648437858458553725910534459624658441549333323759926418",
                "-165714793625005623409248620068089174907473461591147995122619530622718248501766",
                "-6799469259790492954244028907316702065850493362011793270200819679048329353962486116720156698284103124419309263629390446885524349964800595654712728732702008",
                "0"
        ),
        std::make_tuple(
                "-44899278342867897178161916408851471645352269498831438830738136848321760750814",
                "65640897397740066190551572165409064134582743288004789061190670791021638623800",
                "20741619054872169012389655756557592489230473789173350230452533942699877872986",
                "-110540175740607963368713488574260535779935012786836227891928807639343399374614",
                "-2947228922936764263278593134565144136359091408470686107551296314838620133777238799282416859095135867114457581255034043407501865610098211516114469689773200",
                "0"
        ),
        std::make_tuple(
                "-100437361129925299864163022994577223572753204070713888111204937089006626491254",
                "38248932537680770601029411713883490518620747926528326546087978398975222618629",
                "-62188428592244529263133611280693733054132456144185561565116958690031403872625",
                "-138686293667606070465192434708460714091373951997242214657292915487981849109883",
                "-3841621850121193689056094050891961595701619324047065344961894814305035892369316483871638988146919771104166481396023419852469300943183134666226048045970766",
                "-2"
        ),
        std::make_tuple(
                "-100437361129925299864163022994577223572753204070713888111204937089006626491254",
                "382489325376807706010",
                "-100437361129925299864163022994577223572753204070713888110822447763629818785244",
                "-100437361129925299864163022994577223572753204070713888111587426414383434197264",
                "-38416218501211936890531400159631954207969985700838638497543395326072553608661814981408315068236540",
                "-262588664483590143531121710969498588281464294305316518755"
        )
    )
);
