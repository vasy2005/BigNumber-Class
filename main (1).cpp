///BigNumber implementare cu clase, Vasilache Stefan

#include <iostream>

using namespace std;

class BigNumber
{
    typedef long long int LL;
    string nr = ""; LL len = 0;

    ///read & write overload
    friend istream& operator>> (istream &fin, BigNumber &a)
    {
        fin >>a.nr; a.len = a.nr.size();
        string &s = a.nr; LL len = a.len;
        for (LL i = 0; i < len/2; ++i) swap(s[i], s[len - i - 1]);
        return fin;
    }

    friend ostream& operator<< (ostream &fout, const BigNumber &a)
    {
        const string &s = a.nr;
        const LL len = a.len;
        for (LL i = len - 1; i >= 0; --i) fout <<s[i];
        return fout;
    }

public:
    ///assignment operator overload
    BigNumber& operator= (const BigNumber &a)
    {
        nr = a.nr; len = a.len;
        return *this;
    }

    BigNumber& operator= (const string &a)
    {
        nr = a; len = a.size();
        for (LL i = 0; i < len/2; ++i) swap(nr[i], nr[len - i - 1]);
        return *this;
    }

    BigNumber& operator= (LL a)
    {
        len = 0; nr.erase();
        if (!a) nr.push_back('0'), len++;
        else
            while (a) nr.push_back(a%10 + '0'), len++, a /= 10;
        return *this;
    }

    ///comparison operator overload
private:
    int comp(const BigNumber &a, const BigNumber &b) const
    {
        if (a.len != b.len) return (a.len < b.len? -1: 1);

        LL i;
        for (i = a.len - 1; i >= 0; --i)
            if (a.nr[i] < b.nr[i]) return -1;
            else
                if (a.nr[i] > b.nr[i]) return 1;
        return 0;
    }

public:
    bool operator== (const BigNumber &a) const
    {
        return (comp(*this, a) == 0);
    }

    bool operator!= (const BigNumber &b) const
    {
        const BigNumber &a = *this;
        return !(a == b);
    }

    bool operator< (const BigNumber &a) const
    {
        return (comp(*this, a) == -1);
    }

    bool operator<= (const BigNumber &b) const
    {
        const BigNumber &a = *this;
        int ok = comp(a, b);
        return (ok == 0 || ok == -1);
    }

    bool operator> (const BigNumber &a) const
    {
        return (comp(*this, a) == 1);
    }

    bool operator>= (const BigNumber &b) const
    {
        const BigNumber &a = *this;
        int ok = comp(a, b);
        return (ok == 0 || ok == 1);
    }

    ///Arithmetic operators overload
    BigNumber operator+ (const BigNumber &a) const
    {
        BigNumber c;
        const BigNumber &x = *this, &y = a;
        LL val, t = 0;
        LL i;

        c.len = max(x.len, y.len);

        for (i = 0; i < c.len; ++i)
        {
            val = (i >= x.len? '0': x.nr[i]) + (i >= y.len? '0': y.nr[i]) - 2*'0' + t;
            c.nr.push_back(val%10 + '0'); t = val / 10;
        }

        if (t) c.nr.push_back(t + '0'), c.len++;

        return c;
    }

    BigNumber& operator+= (const BigNumber &b)
    {
        BigNumber &a = *this;
        a = a + b;
        return a;
    }

    BigNumber operator- (const BigNumber &a) const
    {
        BigNumber c;
        const BigNumber &x = *this, &y = a;
        LL val, t = 0;
        LL i;

        c.len = x.len;

        for (i = 0; i < c.len; ++i)
        {
            val = (i >= x.len? '0': x.nr[i]) - (i >= y.len? '0': y.nr[i]) + t;
            val < 0? t = -1, val += 10: t = 0;
            c.nr.push_back(val + '0');
        }

        while (c.len > 1 && c.nr[c.len - 1] == '0') c.len--;

        return c;
    }

    BigNumber& operator-= (const BigNumber &b)
    {
        BigNumber &a = *this;
        a = a - b;
        return a;
    }

    BigNumber operator* (const LL &a) const
    {
        BigNumber c;
        const BigNumber &x = *this;
        LL val, t = 0;
        LL i;

        c.len = x.len;

        for (i = 0; i < c.len; ++i)
        {
            val = (x.nr[i] - '0') * a + t;
            c.nr.push_back(val%10 + '0'); t = val / 10;
        }

        while (t)
        {
            c.nr.push_back(t%10 + '0'); t /= 10;
            c.len ++;
        }

        while (c.len > 1 && c.nr[c.len - 1] == '0') c.len --;

        return c;
    }

    BigNumber& operator*= (const LL& b)
    {
        BigNumber &a = *this;
        a = a * b;
        return a;
    }

    BigNumber operator* (const BigNumber& a) const
    {
        BigNumber c;
        const BigNumber &x = *this, &y = a;
        LL val, t;
        LL i, j;

        c.len = x.len + y.len - 1;
        c.nr.replace(0, 1, (x.len + y.len)*2, '0');

        for (i = 0; i < x.len; ++i)
            for (j = 0; j < y.len; ++j)
            {
                val = c.nr[i + j] - '0' + (x.nr[i] - '0') * (y.nr[j] - '0');
                t = c.nr[i + j + 1] - '0' + val / 10; val %= 10;
                c.nr[i + j] = val + '0'; c.nr[i + j + 1] = t + '0';
            }

        while (c.nr[c.len] - '0' > 0)
        {
            c.len ++;
            c.nr[c.len - 1] -= '0'; c.nr[c.len] -= '0';

            c.nr[c.len] = c.nr[c.len - 1] / 10;
            c.nr[c.len - 1] %= 10;

            c.nr[c.len - 1] += '0'; c.nr[c.len] += '0';
        }

        while (c.len > 1 && c.nr[c.len - 1] == '0') c.len --;

        return c;
    }

    friend BigNumber operator* (const LL &a, const BigNumber &b)
    {
        return b*a;
    }

    BigNumber& operator*= (const BigNumber& b)
    {
        BigNumber &a = *this;
        a = a * b;
        return a;
    }

private:
    BigNumber divideLL(const BigNumber &a, const LL &b, LL &rest) const
    {
        BigNumber c;
        LL i, t = 0;
        c.nr = " ";
        if (!b)
        {
            cout <<"Division by 0 is not possible!";
            exit(1);
        }

        c.len = a.len;
        c.nr.replace(0, 1, c.len + 2, '0');

        for (i = a.len - 1; i >= 0; --i)
        {
            t = t * 10 + a.nr[i] - '0';
            c.nr[i] = t/b + '0'; t %= b;
        }

        while (c.len > 1 && c.nr[c.len - 1] == '0') c.len --;

        rest = t;

        return c;
    }

    BigNumber divideBigNumber(const BigNumber &a, const BigNumber &b, BigNumber &rest) const
    {
        BigNumber c; BigNumber r;
        LL i;
        if (b.nr[0] == '0' && b.len == 1)
        {
            cout <<"Division by 0 is not possible!";
            exit(1);
        }

        if (a < b)
        {
            c.nr.push_back('0'); c.len = 1;
            rest = a;
            return c;
        }

        r.len = 0;
        c.len = a.len;
        c.nr.replace(0, 1, c.len + 2, '0');

        for (i = a.len - 1; i >= 0; --i)
        {
            for (int j = r.len; j >= 1; --j) r.nr[j] = r.nr[j - 1];
            r.len ++;
            r.nr[0] = a.nr[i];

            c.nr[i] = '0';

            while (b <= r)
            {
                c.nr[i] ++;
                r -= b;
            }
        }

        while (c.len > 1 && c.nr[c.len - 1] == '0') c.len --;

        rest = r;

        return c;
    }

public:
    BigNumber operator/ (const LL &b) const
    {
        LL rest = 0; const BigNumber &a = *this;
        return divideLL(a, b, rest);
    }

    BigNumber& operator/= (const LL &b)
    {
        LL rest = 0; BigNumber &a = *this;
        a = divideLL(a, b, rest);
        return a;
    }

    LL operator% (const LL &a) const
    {
        LL rest = 0;
        divideLL(*this, a, rest);
        return rest;
    }

    BigNumber& operator%= (const LL &b)
    {
        LL rest = 0; BigNumber &a = *this;
        divideLL(a, b, rest);
        a = rest;
        return a;
    }

    BigNumber operator/ (const BigNumber &b) const
    {
        const BigNumber &a = *this;
        BigNumber rest;
        return divideBigNumber(a, b, rest);
    }

    BigNumber& operator/= (const BigNumber &b)
    {
        BigNumber &a = *this;
        BigNumber rest;
        a = divideBigNumber(a, b, rest);
        return a;
    }

    BigNumber operator% (const BigNumber &b) const
    {
        const BigNumber &a = *this;
        BigNumber rest;
        divideBigNumber(a, b, rest);
        return rest;
    }

    BigNumber& operator%= (const BigNumber &b)
    {
        BigNumber &a = *this;
        BigNumber rest;
        a = divideBigNumber(a, b, rest);
        return a;
    }

    ///Bitwise operators overload
    BigNumber operator<< (const LL& a) const
    {
        LL i; BigNumber x = *this;
        for (i = 1; i <= a; ++i) x *= 2;
        return x;
    }

    BigNumber& operator<<= (const LL& a)
    {
        LL i; BigNumber &x = *this;
        for (i = 1; i <= a; ++i) x *= 2;
        return x;
    }

    BigNumber operator>> (const LL& a) const
    {
        LL i; BigNumber x = *this;
        for (i = 1; i <= a; ++i) x /= 2;
        return x;
    }

    BigNumber& operator>>= (const LL& a)
    {
        LL i; BigNumber &x = *this;
        for (i = 1; i <= a; ++i) x /= 2;
        return x;
    }

    ///Misc
    string toString()
    {
        const BigNumber &a = *this;
        string s = a.nr; LL len = a.len;
        for (LL i = 0; i < len/2; ++i) swap(s[i], s[len - i - 1]);
        return s;
    }
};

BigNumber a, b, c, d, e;

int main()
{
    cin >>a>>b>>c; d = "1234567890"; e = 1234;
    cout <<a*b + c<<' '<<d/a*e%d<<'\n';
    e = 0;
    cout <<e/d<<' '<<e<<' '<<d/e<<' '<<'\n';
    //cout <<d/0;
    cout <<a<<' '<<b<<' '<<c<<' '<<d<<' '<<(a + c + d >= b - d + 2*4*a*c/d)<<' '<<(a*=b+=c*d)<<'\n';
    cout <<(a <<= 2)<<'\n';
    string test = a.toString();
    cout <<test<<'\n';
    return 0;
}
