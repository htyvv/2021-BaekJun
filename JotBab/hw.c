#include <cstdio>
#include <cstdlib>      // rand() 함수를 위함
#include <ctime>        // time() 함수를 위함
extern double tElapsed;   // 게임 소요 시간
extern double playSpeedGugu(int nPlay);



static int NumGames = 0;   // 전체 시도 횟수
static int NumWins = 0;   // 맞힌 횟수
static double Score = 0;   // 점수
double tElapsed = 0;       // 게임 소요시간

double playSpeedGames(int nPlay, int gameNum, int nDigit = 0)
{
    clock_t   t0 = clock();
    for (int i = 0; i < nPlay; i++) {
        if (gameNum == 1) {
            if (playGuguOnce() == false)
                printf("\t틀렸습니다.\n");
        }
        else if (gameNum == 2) {
            if (playMultOnce() == false)
                printf("\t틀렸습니다.\n");
        }
        else if (3 <= gameNum && gameNum <= 9) {
            if (playPlusOnce(nDigit) == false)
                printf("\t틀렸습니다.\n");
        }
    }
    clock_t   t1 = clock();
    tElapsed = (double)(t1 - t0) / CLOCKS_PER_SEC;
    Score = (NumGames > NumWins) ? 0.0
        : 100 * (5.0 * NumGames - tElapsed) / (5.0 * NumGames);
    return Score;
}

static bool playGuguOnce()
{
    int   a = rand() % 8 + 2;
    int   b = rand() % 8 + 2;
    int   result;

    NumGames++;
    printf("[문제%2d]: %2d x %2d = ", NumGames, a, b);
    scanf_s("%d", &result);
    if (result == a * b) NumWins++;
    return (result == a * b);
}

static bool playPlusOnce(int nDigits)
{
    int start = pow(10.0, (double)nDigits - 1); 
    int end = pow(10.0, (double)nDigits) - 1;

    int a = rand() % (end + 1 - start) + start;
    int b = rand() % (end + 1 - start) + start;
    
    int   result;

    NumGames++;
    printf("[문제%2d]:\t%d\t+\t%d\t= ", NumGames, a, b);
    scanf_s("%d", &result);
    if (result == a + b) NumWins++;
    return (result == a + b);
}

static bool playMultOnce()
{
    int start = 10;
    int end = 99;
    int a = rand() % (end + 1 - start) + start;
    int b = rand() % (end + 1 - start) + start;

    int   result;

    NumGames++;
    printf("[문제%2d]: %2d x %2d = ", NumGames, a, b);
    scanf_s("%d", &result);
    if (result == a * b) NumWins++;
    return (result == a * b);
}

void init() {
    NumGames = 0;   // 전체 시도 횟수 초기화
    NumWins = 0;   // 맞힌 횟수 초기화
    Score = 0;   // 점수 초기화
    tElapsed = 0;       // 게임 소요시간 초기화
}

void main()
{
    srand((unsigned)time(NULL));

    int nPlay = 10;
    printf("[스피드 구구단 게임]\n\n");
    printf(" 당신의 구구단 실력을 테스트하세요.!!!\n");
    printf(" %d번 테스트 하겠습니다.\n", nPlay);
    printf(" 크게 심호흡을 하시고...\n 준비되면 엔터를 누르세요...");
    getchar();
    system("cls");

    double score = playSpeedMult(nPlay);
    printf("\n점수 = %4.1f점(총 %4.1f초)\n", score, tElapsed);
}