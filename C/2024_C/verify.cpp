// ./verify in out prog_out
// Returns 0 if the result is correct; otherwise, returns 1 and print error message to stderr.

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::pair;
using std::fstream;
using std::to_string;

using pll = std::pair<long long, long long>;
void inline ensure_that (bool c, const std::string& str) { if (!c) { std::cerr << str << std::endl; exit(1); } }
template<class T> T get_var(std::istream& f) { T v; f >> v; return v; }
pll get_var(std::istream& f) { long long v1 = 0; long long v2 = 0; f >> v1 >> v2; return std::make_pair(v1,v2); }

bool end_of_file_reached (fstream& f)
{
    try { get_var<string>(f); return false; }
    catch (std::ios_base::failure& err) { return true; }
}


void read_result (std::istream& f, int F, const vector<pll>& C, long long P_ref)
{
    auto P = get_var<long long>(f);
    ensure_that (P == P_ref, "Expected " + to_string(P_ref) + ", got " + to_string(P));
    long long value = 0;
    long long weight = 0;
    for (const auto& it : C) {
        int x = get_var<int>(f);
        ensure_that (0 <= x && x <= F, "Value is negative or too large");
        value += it.first * x;
        weight += it.second * x;
    }
    ensure_that(weight == F, "Total weight is " + to_string(weight) + ", but it should be " + to_string(F));
    ensure_that(value == P, "Total value is " + to_string(value) + ", but it should be " + to_string(P));
}


int main(int argc, char* argv[])
{
    assert (argc == 4);
    const vector<char*> args(argv+1, argv+argc);
    fstream in;

    // Read input
    in.exceptions (std::fstream::failbit);
    in.open (args[0], std::fstream::in);
    int F = get_var<int>(in);
    int coins = get_var<int>(in);
    vector<pll> C(coins);
    for (auto& it : C)
        it = get_var(in);
    in.close();

    // Read expected output
    fstream out;
    out.exceptions (std::fstream::failbit);
    out.open (args[1], std::fstream::in);
    auto exp_answer = get_var<string>(out);
    long long exp_P_min = -1;
    long long exp_P_max = -1;
    if (exp_answer == "TAK") {
        exp_P_min = get_var<long long>(out);
        for ([[maybe_unused]] const auto& it : C)
            get_var<int>(out);
        exp_P_max = get_var<long long>(out);
    }
    out.close();

    // Read program output and verify it
    fstream prog_out;
    prog_out.exceptions (std::fstream::failbit);
    prog_out.open (args[2], std::fstream::in);
    try {
        auto answer = get_var<string>(prog_out);
        ensure_that (exp_answer == string(answer), "Expected " + exp_answer + ", got " + answer);
        if (exp_answer == "TAK") {
            read_result (prog_out, F, C, exp_P_min);
            read_result (prog_out, F, C, exp_P_max);
        }
    } catch (std::ios_base::failure& err) {
        ensure_that(false, "Parsing error");
    }
    ensure_that (end_of_file_reached(prog_out), "Output contains superfluous string(s)");
    prog_out.close();
}
