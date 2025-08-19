#include <iostream>
#include <regex>

int main() {
    // HTML과 유사한 문자열을 raw string literal로 저장
    std::string html = R"(
        <div class="social-login">
          <div class="small-comment">다음으로 로그인 </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            또는 직접 입력하세요 (댓글 수정시 비밀번호가 필요합니다)
          </div>
          <input name="name" id="name" placeholder="이름">
          <input name="password" id="password" type="password" placeholder="비밀번호">
        </div>
        <div id="adding-comment" class="sk-fading-circle">
          <div class="sk-circle1 sk-circle">a</div>
          <div class="sk-circle2 sk-circle">b</div>
          <div class="sk-circle3 sk-circle">asd</div>
          <div class="sk-circle4 sk-circle">asdfasf</div>
          <div class="sk-circle5 sk-circle">123</div>
          <div class="sk-circle6 sk-circle">aax</div>
          <div class="sk-circle7 sk-circle">sxz</div>
        </div>
  )";

    // 정규표현식 패턴 정의
    // R"(...)" 는 C++11 이상에서 지원하는 raw string literal
    // 패턴 "<div class=\"sk[\w -]*\">\w*</div>" 설명:
    // - sk로 시작하는 클래스명 (단어 문자, 공백, 하이픈 포함 0개 이상)
    // - div 내부에는 단어 문자(알파벳, 숫자, _ ) 0개 이상 포함
    std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");

    std::smatch match;  // 매칭 결과 저장용 객체

    // html 문자열에서 패턴과 일치하는 부분을 반복적으로 탐색
    while (std::regex_search(html, match, re)) {
        // 매칭된 문자열 출력
        std::cout << match.str() << '\n';

        // 탐색 대상 문자열을 매칭 부분 이후로 변경하여 루프 계속
        html = match.suffix();
}