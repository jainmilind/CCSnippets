inline int mul(const int a, const int b) { return 1ll * a * b % mod; }
inline int add(int a, const int b) { return (a += b) < mod ? a : a - mod; }
inline void addeq(int& a, const int b) { (a += b) >= mod && (a -= mod); }