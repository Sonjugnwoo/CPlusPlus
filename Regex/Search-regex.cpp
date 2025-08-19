#include <iostream>
#include <regex>

int main() {
    // HTML�� ������ ���ڿ��� raw string literal�� ����
    std::string html = R"(
        <div class="social-login">
          <div class="small-comment">�������� �α��� </div>
          <div>
            <i class="xi-facebook-official fb-login"></i>
            <i class="xi-google-plus goog-login"></i>
          </div>
        </div>
        <div class="manual">
          <div class="small-comment">
            �Ǵ� ���� �Է��ϼ��� (��� ������ ��й�ȣ�� �ʿ��մϴ�)
          </div>
          <input name="name" id="name" placeholder="�̸�">
          <input name="password" id="password" type="password" placeholder="��й�ȣ">
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

    // ����ǥ���� ���� ����
    // R"(...)" �� C++11 �̻󿡼� �����ϴ� raw string literal
    // ���� "<div class=\"sk[\w -]*\">\w*</div>" ����:
    // - sk�� �����ϴ� Ŭ������ (�ܾ� ����, ����, ������ ���� 0�� �̻�)
    // - div ���ο��� �ܾ� ����(���ĺ�, ����, _ ) 0�� �̻� ����
    std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");

    std::smatch match;  // ��Ī ��� ����� ��ü

    // html ���ڿ����� ���ϰ� ��ġ�ϴ� �κ��� �ݺ������� Ž��
    while (std::regex_search(html, match, re)) {
        // ��Ī�� ���ڿ� ���
        std::cout << match.str() << '\n';

        // Ž�� ��� ���ڿ��� ��Ī �κ� ���ķ� �����Ͽ� ���� ���
        html = match.suffix();
}