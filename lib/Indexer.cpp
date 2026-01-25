//using ll = long long;
//const ll LINF = 1e18;

static constexpr int LINF = numeric_limits<int>::max() / 4;

struct StringIndexer {
    string s;          // 元の文字列
    int n = 0;         // 文字列長

    // right_pos[c][i] : 位置 i より「右側」で最も近い文字 c の位置（なければ INF）
    // left_pos[c][i]  : 位置 i より「左側」で最も近い文字 c の位置（なければ -1）
    array<vector<int>, 26> right_pos;
    array<vector<int>, 26> left_pos;

    StringIndexer() = default;
    explicit StringIndexer(const string &str) { init(str); }

    // 初期化
    void init(const string &str) {
        s = str;
        n = (int)s.size();

        for (int c = 0; c < 26; ++c) {
            right_pos[c].assign(n, LINF);
            left_pos[c].assign(n, -1);
        }

        if (n == 0) return; // 空文字列は何もしない

        // right_pos の構築
        // right_pos[c][i] = min{ j > i | s[j] == c }
        for (int i = n - 2; i >= 0; --i) {
            for (int c = 0; c < 26; ++c) right_pos[c][i] = right_pos[c][i + 1];
            int idx = s[i + 1] - 'a';
            if (0 <= idx && idx < 26) right_pos[idx][i] = i + 1;
        }

        // left_pos の構築
        // left_pos[c][i] = max{ j < i | s[j] == c }
        for (int i = 1; i < n; ++i) {
            for (int c = 0; c < 26; ++c) left_pos[c][i] = left_pos[c][i - 1];
            int idx = s[i - 1] - 'a';
            if (0 <= idx && idx < 26) left_pos[idx][i] = i - 1;
        }
    }

    // 現在位置 cur から、文字 ch の「右側で一番近い位置」へ移動する
    // cur < 0 のときは「文字列の左外」からスタートしたとみなす
    // 見つからなければ LINF を返す
    inline int go_right(int cur, char ch) const {
        if (n == 0) return LINF;
        if (cur == LINF) return LINF;
        int c = ch - 'a';
        if (c < 0 || c >= 26) return LINF;
        if (cur < 0) {
            if (s[0] == ch) return 0;
            cur = 0;
        }
        return right_pos[c][cur];
    }

    // 現在位置 cur から、文字 ch の「左側で一番近い位置」へ移動する
    // 見つからなければ -1 を返す
    inline int go_left(int cur, char ch) const {
        if (n == 0) return -1;
        if (cur < 0) return cur;
        int c = ch - 'a';
        if (c < 0 || c >= 26) return -1;
        return left_pos[c][cur];
    }

    // 【部分列判定用ユーティリティ】
    // start の「右」から文字列 t を順にたどれるかを判定する
    // すべてたどれた場合: 最後に一致した位置を返す
    // 途中で失敗した場合: LINF を返す
    //
    // 例:
    //   s = "abac", start = -1, t = "ac"
    //   - 'a' -> 0
    //   - 'c' -> 3
    //   => 3 を返す
    int match_subsequence_from(int start, const string &t) const {
        int cur = start;
        for (char ch : t) {
            cur = go_right(cur, ch);
            if (cur == LINF) return LINF;
        }
        return cur;
    }
};
