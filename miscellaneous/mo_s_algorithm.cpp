const int blk = 400;
struct query {
    int id, l, r;
    bool operator<(query b) const {
        if (l / blk != b.l / blk)
            return  make_pair(l / blk, r) < make_pair(b.l / blk, b.r);
        return (l / blk & 1) ? (r < b.r) : (r > b.r);
    }
};

vector<int> mos_algo(vector<query>& q) {
    sort(begin(q), end(q));
    int m = q.size();
    int cur_r = -1, cur_l = 0, cur = 0;
    vector<int> ans(m);

    auto add = [&](int i) {

    };

    auto remove = [&](int i) {

    };

    auto get_ans = [&]() {

    };

    for (auto x : q) {
        while (cur_l > x.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_l < x.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > x.r) {
            remove(cur_r);
            cur_r--;
        }
        while (cur_r < x.r) {
            cur_r++;
            add(cur_r);
        }
        ans[x.id] = get_ans();
    }

    return ans;
}
