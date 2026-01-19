//
// Created by noname on 2.01.2026.
//

#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <list>

#include <gtest/gtest.h>

import realn.codebox.core;

TEST(cbcore_strings, conversion) {
    using namespace std::string_literals;

    //simple cast
    EXPECT_EQ(realn::cb::cast_string_to_u8("some text"), std::u8string{u8"some text"});
    EXPECT_EQ(realn::cb::cast_u8_to_string(u8"some text"), std::string{"some text"});

    //simple conversion
    EXPECT_EQ(realn::cb::utf_convert_to_u8(u"some text"), std::u8string{u8"some text"});
    EXPECT_EQ(realn::cb::utf_convert_to_u8(U"some text"), std::u8string{u8"some text"});
    EXPECT_EQ(realn::cb::utf_convert_to_u16(u8"some text"), std::u16string{u"some text"});
    EXPECT_EQ(realn::cb::utf_convert_to_u16(U"some text"), std::u16string{u"some text"});
    EXPECT_EQ(realn::cb::utf_convert_to_u32(u8"some text"), std::u32string{U"some text"});
    EXPECT_EQ(realn::cb::utf_convert_to_u32(u"some text"), std::u32string{U"some text"});

    //more complex conversions
    EXPECT_EQ(realn::cb::utf_convert_to_u8(u"źdźbło trawy ścieka w szczękę dżdżownicy równo"),
              std::u8string{u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"});
    EXPECT_EQ(realn::cb::utf_convert_to_u8(U"źdźbło trawy ścieka w szczękę dżdżownicy równo"),
              std::u8string{u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"});
    EXPECT_EQ(realn::cb::utf_convert_to_u16(u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"),
              std::u16string{u"źdźbło trawy ścieka w szczękę dżdżownicy równo"});
    EXPECT_EQ(realn::cb::utf_convert_to_u16(U"źdźbło trawy ścieka w szczękę dżdżownicy równo"),
              std::u16string{u"źdźbło trawy ścieka w szczękę dżdżownicy równo"});
    EXPECT_EQ(realn::cb::utf_convert_to_u32(u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"),
              std::u32string{U"źdźbło trawy ścieka w szczękę dżdżownicy równo"});
    EXPECT_EQ(realn::cb::utf_convert_to_u32(u"źdźbło trawy ścieka w szczękę dżdżownicy równo"),
              std::u32string{U"źdźbło trawy ścieka w szczękę dżdżownicy równo"});

    //complex conversions
    EXPECT_EQ(realn::cb::utf_convert_to_u8(u"複雑なものと単純なものは同じである"),
              std::u8string{u8"複雑なものと単純なものは同じである"});
    EXPECT_EQ(realn::cb::utf_convert_to_u8(U"複雑なものと単純なものは同じである"),
              std::u8string{u8"複雑なものと単純なものは同じである"});
    EXPECT_EQ(realn::cb::utf_convert_to_u16(u8"複雑なものと単純なものは同じである"),
              std::u16string{u"複雑なものと単純なものは同じである"});
    EXPECT_EQ(realn::cb::utf_convert_to_u16(U"複雑なものと単純なものは同じである"),
              std::u16string{u"複雑なものと単純なものは同じである"});
    EXPECT_EQ(realn::cb::utf_convert_to_u32(u8"複雑なものと単純なものは同じである"),
              std::u32string{U"複雑なものと単純なものは同じである"});
    EXPECT_EQ(realn::cb::utf_convert_to_u32(u"複雑なものと単純なものは同じである"),
              std::u32string{U"複雑なものと単純なものは同じである"});
}

TEST(cbcore_strings, bool_conversion) {
    using namespace std::string_literals;
    using namespace realn;

    EXPECT_EQ(cb::bool_to_string(true), "true"s);
    EXPECT_EQ(cb::bool_to_string(false), "false"s);
    EXPECT_EQ(cb::bool_to_string(true, cb::to_string_conv_type::LOWER), "true"s);
    EXPECT_EQ(cb::bool_to_string(false, cb::to_string_conv_type::LOWER), "false"s);
    EXPECT_EQ(cb::bool_to_string(true, cb::to_string_conv_type::CAPITALIZED), "True"s);
    EXPECT_EQ(cb::bool_to_string(false, cb::to_string_conv_type::CAPITALIZED), "False"s);
    EXPECT_EQ(cb::bool_to_string(true, cb::to_string_conv_type::HIGHER), "TRUE"s);
    EXPECT_EQ(cb::bool_to_string(false, cb::to_string_conv_type::HIGHER), "FALSE"s);

    EXPECT_EQ(cb::bool_to_utf8(true), u8"true"s);
    EXPECT_EQ(cb::bool_to_utf8(false), u8"false"s);
    EXPECT_EQ(cb::bool_to_utf8(true, cb::to_string_conv_type::LOWER), u8"true"s);
    EXPECT_EQ(cb::bool_to_utf8(false, cb::to_string_conv_type::LOWER), u8"false"s);
    EXPECT_EQ(cb::bool_to_utf8(true, cb::to_string_conv_type::CAPITALIZED), u8"True"s);
    EXPECT_EQ(cb::bool_to_utf8(false, cb::to_string_conv_type::CAPITALIZED), u8"False"s);
    EXPECT_EQ(cb::bool_to_utf8(true, cb::to_string_conv_type::HIGHER), u8"TRUE"s);
    EXPECT_EQ(cb::bool_to_utf8(false, cb::to_string_conv_type::HIGHER), u8"FALSE"s);

    EXPECT_EQ(cb::bool_to_utf16(true), u"true"s);
    EXPECT_EQ(cb::bool_to_utf16(false), u"false"s);
    EXPECT_EQ(cb::bool_to_utf16(true, cb::to_string_conv_type::LOWER), u"true"s);
    EXPECT_EQ(cb::bool_to_utf16(false, cb::to_string_conv_type::LOWER), u"false"s);
    EXPECT_EQ(cb::bool_to_utf16(true, cb::to_string_conv_type::CAPITALIZED), u"True"s);
    EXPECT_EQ(cb::bool_to_utf16(false, cb::to_string_conv_type::CAPITALIZED), u"False"s);
    EXPECT_EQ(cb::bool_to_utf16(true, cb::to_string_conv_type::HIGHER), u"TRUE"s);
    EXPECT_EQ(cb::bool_to_utf16(false, cb::to_string_conv_type::HIGHER), u"FALSE"s);

    EXPECT_EQ(cb::bool_to_utf32(true), U"true"s);
    EXPECT_EQ(cb::bool_to_utf32(false), U"false"s);
    EXPECT_EQ(cb::bool_to_utf32(true, cb::to_string_conv_type::LOWER), U"true"s);
    EXPECT_EQ(cb::bool_to_utf32(false, cb::to_string_conv_type::LOWER), U"false"s);
    EXPECT_EQ(cb::bool_to_utf32(true, cb::to_string_conv_type::CAPITALIZED), U"True"s);
    EXPECT_EQ(cb::bool_to_utf32(false, cb::to_string_conv_type::CAPITALIZED), U"False"s);
    EXPECT_EQ(cb::bool_to_utf32(true, cb::to_string_conv_type::HIGHER), U"TRUE"s);
    EXPECT_EQ(cb::bool_to_utf32(false, cb::to_string_conv_type::HIGHER), U"FALSE"s);

    bool result = false;
    EXPECT_THROW(cb::string_to_bool("invalid"s), std::runtime_error);
    EXPECT_NO_THROW(cb::string_to_bool("invalid"s, &result));
    EXPECT_FALSE(result);

    EXPECT_EQ(cb::string_to_bool("true"s), true);
    EXPECT_EQ(cb::string_to_bool("True"s), true);
    EXPECT_EQ(cb::string_to_bool("TRUE"s), true);
    EXPECT_EQ(cb::string_to_bool(u8"true"s), true);
    EXPECT_EQ(cb::string_to_bool(u8"True"s), true);
    EXPECT_EQ(cb::string_to_bool(u8"TRUE"s), true);
    EXPECT_EQ(cb::string_to_bool(u"true"s), true);
    EXPECT_EQ(cb::string_to_bool(u"True"s), true);
    EXPECT_EQ(cb::string_to_bool(u"TRUE"s), true);
    EXPECT_EQ(cb::string_to_bool(U"true"s), true);
    EXPECT_EQ(cb::string_to_bool(U"True"s), true);
    EXPECT_EQ(cb::string_to_bool(U"TRUE"s), true);

    EXPECT_EQ(cb::string_to_bool("false"s), false);
    EXPECT_EQ(cb::string_to_bool("False"s), false);
    EXPECT_EQ(cb::string_to_bool("FALSE"s), false);
    EXPECT_EQ(cb::string_to_bool(u8"false"s), false);
    EXPECT_EQ(cb::string_to_bool(u8"False"s), false);
    EXPECT_EQ(cb::string_to_bool(u8"FALSE"s), false);
    EXPECT_EQ(cb::string_to_bool(u"false"s), false);
    EXPECT_EQ(cb::string_to_bool(u"False"s), false);
    EXPECT_EQ(cb::string_to_bool(u"FALSE"s), false);
    EXPECT_EQ(cb::string_to_bool(U"false"s), false);
    EXPECT_EQ(cb::string_to_bool(U"False"s), false);
    EXPECT_EQ(cb::string_to_bool(U"FALSE"s), false);
}

TEST(cbcore_strings, utf_length) {
    using namespace std::string_literals;
    using namespace realn;

    const auto test_text_str = "some_text"s;
    const auto test_text_utf8 = u8"some text"s;

    EXPECT_EQ(cb::utf_length(test_text_str), 9);
    EXPECT_EQ(cb::utf_length(test_text_str), test_text_str.length());
    EXPECT_EQ(cb::utf_length(test_text_utf8), 9);
    EXPECT_EQ(cb::utf_length(test_text_utf8), test_text_utf8.length());

    const auto test_text2_str = "サンプル"s;
    const auto test_text2_utf8 = u8"サンプル"s;

    EXPECT_EQ(cb::utf_length(test_text2_str), 4);
    EXPECT_NE(cb::utf_length(test_text2_str), test_text2_str.length());
    EXPECT_EQ(cb::utf_length(test_text2_utf8), 4);
    EXPECT_NE(cb::utf_length(test_text2_utf8), test_text2_utf8.length());
}

TEST(cbcore_strings, utf_bom) {
    using namespace std::string_literals;
    using namespace realn;

    const auto test_text_str = "some_text"s;
    const auto test_text_utf8 = u8"some text"s;

    const auto test_text_with_bom_str = "\xef\xbb\xbfsome_text"s;
    const auto test_text_with_bom_utf8 = u8"\xef\xbb\xbfsome text"s;

    const auto wrong_bom_str = test_text_str + test_text_with_bom_str;
    const auto wrong_bom_utf8 = test_text_utf8 + test_text_with_bom_utf8;

    EXPECT_FALSE(cb::starts_with_utf8_bom(test_text_str));
    EXPECT_FALSE(cb::starts_with_utf8_bom(test_text_utf8));

    EXPECT_TRUE(cb::starts_with_utf8_bom(test_text_with_bom_str));
    EXPECT_TRUE(cb::starts_with_utf8_bom(test_text_with_bom_utf8));

    EXPECT_FALSE(cb::starts_with_utf8_bom(wrong_bom_str));
    EXPECT_FALSE(cb::starts_with_utf8_bom(wrong_bom_utf8));
}

TEST(cbcore_strings, utf8_validation) {
    using namespace std::string_literals;
    using namespace realn;

    const auto valid_text1_str = "some_text"s;
    const auto valid_text2_str = "źdźbło trawy ścieka w szczękę dżdżownicy równo"s;
    const auto valid_text3_str = "複雑なものと単純なものは同じである"s;

    const auto valid_text1_utf8 = u8"some_text"s;
    const auto valid_text2_utf8 = u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s;
    const auto valid_text3_utf8 = u8"複雑なものと単純なものは同じである"s;

    const auto invalid_text1_str = "\x43\xf1\xf4"s;
    const auto invalid_text2_str = "źdź\xf3ło trawy ścieka w\xf8szczękę dżdżownicy równo"s;
    const auto invalid_text3_str = "複雑なもの\x01と単純なも\xf0のは同じで\xffある"s;

    const auto invalid_text1_utf8 = u8"\x43\xf1\xf4"s;
    const auto invalid_text2_utf8 = u8"źdź\xf3ło trawy ścieka w\xf8szczękę dżdżownicy równo"s;
    const auto invalid_text3_utf8 = u8"複雑なもの\x01と単純なも\xf0のは同じで\xffある"s;

    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text1_str));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text2_str));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text3_str));

    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text1_utf8));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text2_utf8));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text3_utf8));

    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text1_str));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text2_str));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text3_str));

    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text1_utf8));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text2_utf8));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text3_utf8));
}

TEST(cbcore_strings, invalid_utf8_replace) {
    using namespace std::string_literals;
    using namespace realn;

    const auto invalid_text1_str = "\x43\xf1\xf4"s;
    const auto invalid_text2_str = "źdź\xf3ło trawy ścieka w\xf8szczękę dżdżownicy równo"s;
    const auto invalid_text3_str = "複雑なもの\x01と単純なも\xf0のは同じで\xffある"s;

    const auto invalid_text1_utf8 = u8"\x43\xf1\xf4"s;
    const auto invalid_text2_utf8 = u8"źdź\xf3ło trawy ścieka w\xf8szczękę dżdżownicy równo"s;
    const auto invalid_text3_utf8 = u8"複雑なもの\x01と単純なも\xf0のは同じで\xffある"s;

    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text1_str));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text2_str));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text3_str));

    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text1_utf8));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text2_utf8));
    EXPECT_FALSE(cb::is_valid_utf8_string(invalid_text3_utf8));

    const auto valid_text1_str = cb::replace_invalid_utf8(invalid_text1_str, '!');
    const auto valid_text2_str = cb::replace_invalid_utf8(invalid_text2_str, '!');
    const auto valid_text3_str = cb::replace_invalid_utf8(invalid_text3_str, '!');

    const auto valid_text1_utf8 = cb::replace_invalid_utf8(invalid_text1_utf8, '!');
    const auto valid_text2_utf8 = cb::replace_invalid_utf8(invalid_text2_utf8, '!');
    const auto valid_text3_utf8 = cb::replace_invalid_utf8(invalid_text3_utf8, '!');

    EXPECT_EQ(valid_text1_str, "C!!"s);
    EXPECT_EQ(valid_text2_str, "źdź!ło trawy ścieka w!szczękę dżdżownicy równo"s);
    EXPECT_EQ(valid_text3_str, "複雑なもの\x01と単純なも!のは同じで!ある"s);

    EXPECT_EQ(valid_text1_utf8, u8"C!!"s);
    EXPECT_EQ(valid_text2_utf8, u8"źdź!ło trawy ścieka w!szczękę dżdżownicy równo"s);
    EXPECT_EQ(valid_text3_utf8, u8"複雑なもの\x01と単純なも!のは同じで!ある"s);

    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text1_str));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text2_str));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text3_str));

    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text1_utf8));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text2_utf8));
    EXPECT_TRUE(cb::is_valid_utf8_string(valid_text3_utf8));
}

TEST(cbcore_strings, count) {
    using namespace std::string_literals;
    using namespace realn;

    EXPECT_EQ(cb::count("testtest testastest"s, "test"s), 4);
    EXPECT_EQ(cb::count(u8"testtest testastest"s, u8"test"s), 4);
    EXPECT_EQ(cb::count(u"testtest testastest"s, u"test"s), 4);
    EXPECT_EQ(cb::count(U"testtest testastest"s, U"test"s), 4);

    EXPECT_EQ(cb::count(u8"tststststs"s, u8"tsts"s), 2);
}

template<class string_type>
void test_sub_compare(const string_type &test_text, const string_type &test_what1, const string_type &test_what2,
                      const std::size_t correct_pos1, const std::size_t correct_pos2) {
    using namespace realn;
    const auto test_what_vector = std::vector{test_what1, test_what2};
    const auto test_what_set = std::set{test_what1, test_what2};
    const auto test_what_uset = std::unordered_set{test_what1, test_what2};

    const auto correct_positions_multi = std::unordered_set{
        correct_pos1, correct_pos2
    };

    for (auto pos = std::size_t{0}; pos < test_text.length(); pos++) {
        SCOPED_TRACE(std::format("Current Pos: {}", pos));
        if (correct_pos1 == pos) {
            EXPECT_TRUE(cb::sub_compare(test_text, test_what1, pos));
        } else {
            EXPECT_FALSE(cb::sub_compare(test_text, test_what1, pos));
        }
        if (correct_positions_multi.contains(pos)) {
            EXPECT_TRUE(cb::sub_compare(test_text, test_what_vector, pos));
            EXPECT_TRUE(cb::sub_compare(test_text, test_what_set, pos));
            EXPECT_TRUE(cb::sub_compare(test_text, test_what_uset, pos));
        } else {
            EXPECT_FALSE(cb::sub_compare(test_text, test_what_vector, pos));
            EXPECT_FALSE(cb::sub_compare(test_text, test_what_set, pos));
            EXPECT_FALSE(cb::sub_compare(test_text, test_what_uset, pos));
        }
    }
}

TEST(cbcore_strings, subcompare) {
    using namespace std::string_literals;

    {
        SCOPED_TRACE("while sub_compare - str testing.");
        test_sub_compare("źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                         "ścieka"s, "dżdżownicy"s, 16, 36);
    }

    {
        SCOPED_TRACE("while sub_compare - utf8 testing.");
        test_sub_compare(u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                         u8"ścieka"s, u8"dżdżownicy"s, 16, 36);
    }

    {
        SCOPED_TRACE("while sub_compare - utf16 testing.");
        test_sub_compare(u"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                         u"ścieka"s, u"dżdżownicy"s, 13, 30);
    }

    {
        SCOPED_TRACE("while sub_compare - utf32 testing.");
        test_sub_compare(U"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                         U"ścieka"s, U"dżdżownicy"s, 13, 30);
    }
}

template<class string_type>
void test_sub_compare_from_back(const string_type &test_text, const string_type &test_what1,
                                const std::size_t correct_pos1) {
    using namespace realn;

    for (auto pos = std::size_t{0}; pos < test_text.length(); pos++) {
        SCOPED_TRACE(std::format("Current Pos: {}", pos));
        if (correct_pos1 == pos) {
            EXPECT_TRUE(cb::sub_compare_from_back(test_text, test_what1, pos));
        } else {
            EXPECT_FALSE(cb::sub_compare_from_back(test_text, test_what1, pos));
        }
    }
}

TEST(cbcore_strings, subcompare_from_back) {
    using namespace std::string_literals;

    {
        SCOPED_TRACE("while sub_compare_from_back - str testing.");
        test_sub_compare_from_back("źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                   "ścieka"s, 39);
    }

    {
        SCOPED_TRACE("while sub_compare_from_back - utf8 testing.");
        test_sub_compare_from_back(u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                   u8"ścieka"s, 39);
    }

    {
        SCOPED_TRACE("while sub_compare_from_back - utf16 testing.");
        test_sub_compare_from_back(u"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                   u"ścieka"s, 33);
    }

    {
        SCOPED_TRACE("while sub_compare_from_back - utf32 testing.");
        test_sub_compare_from_back(U"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                   U"ścieka"s, 33);
    }
}

template<class string_type>
void test_sub_compare_from_word_back(const string_type &test_text, const string_type &test_what1,
                                     const std::size_t correct_pos1) {
    using namespace realn;

    for (auto pos = std::size_t{0}; pos < test_text.length(); pos++) {
        SCOPED_TRACE(std::format("Current Pos: {}", pos));
        if (correct_pos1 == pos) {
            EXPECT_TRUE(cb::sub_compare_from_word_back(test_text, test_what1, pos));
        } else {
            EXPECT_FALSE(cb::sub_compare_from_word_back(test_text, test_what1, pos));
        }
    }
}

TEST(cbcore_strings, subcompare_from_word_back) {
    using namespace std::string_literals;

    {
        SCOPED_TRACE("while sub_compare_from_word_back - str testing.");
        test_sub_compare_from_word_back("źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                        "ścieka"s, 23);
    }

    {
        SCOPED_TRACE("while sub_compare_from_word_back - utf8 testing.");
        test_sub_compare_from_word_back(u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                        u8"ścieka"s, 23);
    }

    {
        SCOPED_TRACE("while sub_compare_from_word_back - utf16 testing.");
        test_sub_compare_from_word_back(u"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                        u"ścieka"s, 19);
    }

    {
        SCOPED_TRACE("while sub_compare_from_word_back - utf32 testing.");
        test_sub_compare_from_word_back(U"źdźbło trawy ścieka w szczękę dżdżownicy równo"s,
                                        U"ścieka"s, 19);
    }
}

template<class string_type, class string_container_type>
void test_sub_find_container(const std::string &test_name,
                             const string_type &test_text,
                             const string_container_type &test_list,
                             const std::map<std::size_t, string_type> &pos_list) {
    using namespace realn;

    SCOPED_TRACE(test_name);
    for (auto pos = std::size_t{0}; pos < test_text.length(); pos++) {
        SCOPED_TRACE(std::format("pos: {}", pos));

        const auto it = cb::sub_find(test_text, test_list, pos);
        if (!pos_list.contains(pos)) {
            EXPECT_EQ(it, test_list.end());
            continue;
        }

        EXPECT_NE(it, test_list.end());
        if (it == test_list.end()) {
            continue;
        }
        const auto &correct_item = pos_list.at(pos);

        EXPECT_EQ(*it, correct_item);
    }
}

template<size_t size, class string_type = std::u8string, class from_u8_func_type>
void test_sub_find_string_type(const std::string &test_name,
                               const std::u8string &u8_test_text,
                               const std::array<std::u8string, size> &u8_test_items,
                               const std::array<std::size_t, size> &vec_pos,
                               const std::array<std::size_t, size> &set_pos,
                               const std::array<std::size_t, size> &uset_pos,
                               from_u8_func_type from_u8) {
    using namespace std::string_literals;

    SCOPED_TRACE(test_name);

    using vector_item_type = std::vector<string_type>;
    using set_item_type = std::set<string_type>;
    using uset_item_type = std::unordered_set<string_type>;

    using correct_pos_map_type = std::map<std::size_t, string_type>;
    auto create_correct_pos_map = [](const std::array<string_type, size> &items,
                                     const std::array<std::size_t, size> &positions) {
        auto result = correct_pos_map_type{};
        for (size_t i = 0; i < size; i++) {
            result[positions[i]] = items[i];
        }
        return result;
    };

    const auto test_text = from_u8(u8_test_text);
    auto test_items = std::array<string_type, size>{};
    std::transform(u8_test_items.begin(), u8_test_items.end(),
                   test_items.begin(),
                   [&](const std::u8string &item) -> string_type { return from_u8(item); });

    const auto test_find_vec_list = vector_item_type{test_items.begin(), test_items.end()};
    const auto test_correct_vec_list = create_correct_pos_map(test_items, vec_pos);

    const auto test_find_set_list = set_item_type{test_items.begin(), test_items.end()};
    const auto test_correct_set_list = create_correct_pos_map(test_items, set_pos);

    const auto test_find_uset_list = uset_item_type{test_items.begin(), test_items.end()};
    const auto test_correct_uset_list = create_correct_pos_map(test_items, uset_pos);

    test_sub_find_container("std::vector", test_text, test_find_vec_list, test_correct_vec_list);
    test_sub_find_container("std::set", test_text, test_find_set_list, test_correct_set_list);
    test_sub_find_container("std::unordered_set", test_text, test_find_uset_list, test_correct_uset_list);
}

TEST(cbcore_strings, sub_find) {
    using namespace std::string_literals;
    using namespace realn;

    const auto test_text = u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s;
    const auto test_items = std::array<std::u8string, 4>{
        u8"trawy"s,
        u8"ka w s"s,
        u8"dżdżownicy"s,
        u8"ło trawy"s,
    };

    constexpr auto str_vec_pos = std::array<std::size_t, 4>{10, 21, 36, 6};
    constexpr auto str_set_pos = std::array<std::size_t, 4>{10, 21, 36, 6};
    constexpr auto str_uset_pos = std::array<std::size_t, 4>{10, 21, 36, 6};

    constexpr auto utf8_vec_pos = std::array<std::size_t, 4>{10, 21, 36, 6};
    constexpr auto utf8_set_pos = std::array<std::size_t, 4>{10, 21, 36, 6};
    constexpr auto utf8_uset_pos = std::array<std::size_t, 4>{10, 21, 36, 6};

    constexpr auto utf16_vec_pos = std::array<std::size_t, 4>{7, 17, 30, 4};
    constexpr auto utf16_set_pos = std::array<std::size_t, 4>{7, 17, 30, 4};
    constexpr auto utf16_uset_pos = std::array<std::size_t, 4>{7, 17, 30, 4};

    constexpr auto utf32_vec_pos = std::array<std::size_t, 4>{7, 17, 30, 4};
    constexpr auto utf32_set_pos = std::array<std::size_t, 4>{7, 17, 30, 4};
    constexpr auto utf32_uset_pos = std::array<std::size_t, 4>{7, 17, 30, 4};

    test_sub_find_string_type<4, std::string>("std::string",
                                              test_text,
                                              test_items,
                                              str_vec_pos,
                                              str_set_pos,
                                              str_uset_pos,
                                              cb::cast_u8_to_string);

    test_sub_find_string_type<4, std::u8string>("std::u8string",
                                                test_text,
                                                test_items,
                                                utf8_vec_pos,
                                                utf8_set_pos,
                                                utf8_uset_pos,
                                                [](const std::u8string &text) { return text; });

    test_sub_find_string_type<4, std::u16string>("std::u16string",
                                                 test_text,
                                                 test_items,
                                                 utf16_vec_pos,
                                                 utf16_set_pos,
                                                 utf16_uset_pos,
                                                 [](const std::u8string &text) {
                                                     return cb::utf_convert_to_u16(text);
                                                 });

    test_sub_find_string_type<4, std::u32string>("std::u32string",
                                                 test_text,
                                                 test_items,
                                                 utf32_vec_pos,
                                                 utf32_set_pos,
                                                 utf32_uset_pos,
                                                 [](const std::u8string &text) {
                                                     return cb::utf_convert_to_u32(text);
                                                 });
}

template<class string_type = std::u8string>
void test_sub_string_by_pos_string_type(const std::string &test_name, const string_type &test_text) {
    using namespace realn;

    SCOPED_TRACE(test_name);
    for (auto sub_length = test_text.length(); sub_length > 0; --sub_length) {
        for (auto pos = size_t{0}; pos < test_text.length() - sub_length; pos++) {
            const auto end_pos = pos + sub_length;
            SCOPED_TRACE(std::format("pos: {}, sub_length: {}", pos, sub_length));

            EXPECT_EQ(cb::sub_string_by_pos(test_text, pos, end_pos), test_text.substr(pos, sub_length));
        }
    }
}

TEST(cbcore_strings, sub_string_by_pos) {
    using namespace std::string_literals;
    using namespace realn;

    const auto test_text_utf8 = u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s;
    const auto test_text_str = cb::cast_u8_to_string(test_text_utf8);
    const auto test_text_utf16 = cb::utf_convert_to_u16(test_text_utf8);
    const auto test_text_utf32 = cb::utf_convert_to_u32(test_text_utf8);

    test_sub_string_by_pos_string_type<std::string>("std::string", test_text_str);
    test_sub_string_by_pos_string_type<std::u8string>("std::string", test_text_utf8);
    test_sub_string_by_pos_string_type<std::u16string>("std::string", test_text_utf16);
    test_sub_string_by_pos_string_type<std::u32string>("std::string", test_text_utf32);
}

template<class from_u8_type = decltype(realn::cb::cast_u8_to_string)>
void test_replace_string_type(const std::string &test_name,
                              const std::u8string &test_text_utf8,
                              const std::u8string &test_target_text_utf8,
                              const std::u8string &test_what_utf8,
                              const std::u8string &test_with_utf8,
                              from_u8_type from_u8) {
    using namespace realn;

    SCOPED_TRACE(test_name);

    const auto test_text = from_u8(test_text_utf8);
    const auto test_target = from_u8(test_target_text_utf8);
    const auto test_what = from_u8(test_what_utf8);
    const auto test_with = from_u8(test_with_utf8);

    EXPECT_EQ(cb::replace(test_text, test_what, test_with), test_target);
    EXPECT_NE(cb::replace(test_text, test_with, test_what), test_target);
    EXPECT_EQ(cb::replace(test_text, test_with, test_what), test_text);
    EXPECT_NE(cb::replace(test_text, test_what, test_what), test_target);
    EXPECT_EQ(cb::replace(test_text, test_what, test_what), test_text);
}

TEST(cbcore_strings, replace) {
    using namespace std::string_literals;
    using namespace realn;

    const auto test_text_utf8 = u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s;
    const auto test_target_utf8 = u8"źdźbło trawy kźerśwa w szczękę dżdżownicy równo"s;
    const auto test_what_utf8 = u8"ścieka"s;
    const auto test_with_ut8 = u8"kźerśwa"s;

    test_replace_string_type("std::string",
                             test_text_utf8,
                             test_target_utf8,
                             test_what_utf8,
                             test_with_ut8,
                             cb::cast_u8_to_string);

    test_replace_string_type("std::u8string",
                             test_text_utf8,
                             test_target_utf8,
                             test_what_utf8,
                             test_with_ut8,
                             [](const std::u8string &item) { return item; });

    test_replace_string_type("std::u16string",
                             test_text_utf8,
                             test_target_utf8,
                             test_what_utf8,
                             test_with_ut8,
                             [](const std::u8string &item) { return cb::utf_convert_to_u16(item); });

    test_replace_string_type("std::u32string",
                             test_text_utf8,
                             test_target_utf8,
                             test_what_utf8,
                             test_with_ut8,
                             [](const std::u8string &item) { return cb::utf_convert_to_u32(item); });
}

template<class string_type = std::string,
    class string_map_type = std::map<string_type, string_type>,
    class from_u8_type = decltype(realn::cb::cast_u8_to_string),
    class append_list_type = decltype([](string_map_type &list, const string_type &, const string_type &) {
    })>
void test_replace_multi_mapped_string_type(const std::string &test_name,
                                           const std::u8string &test_text_utf8,
                                           const std::u8string &test_target_text_utf8,
                                           const std::unordered_map<std::u8string, std::u8string> &test_list_utf8,
                                           from_u8_type from_u8,
                                           append_list_type append_list) {
    using namespace realn;

    SCOPED_TRACE(test_name);

    const auto test_text = from_u8(test_text_utf8);
    const auto test_target = from_u8(test_target_text_utf8);
    auto test_list = string_map_type{};
    for (const auto &[what, with]: test_list_utf8) {
        append_list(test_list, from_u8(what), from_u8(with));
    }

    EXPECT_EQ(cb::replace(test_text, test_list), test_target);
    EXPECT_NE(cb::replace(test_text, test_list), test_target);

    EXPECT_EQ(cb::replace(test_text, test_list), test_text);
    EXPECT_NE(cb::replace(test_text, test_list), test_target);
    EXPECT_EQ(cb::replace(test_text, test_list), test_text);
}

template<class string_type = std::string, class from_u8_type = decltype(realn::cb::cast_u8_to_string)>
void test_replace_multi_string_type(const std::string &test_name,
                                    const std::u8string &test_text_utf8,
                                    const std::u8string &test_target_text_utf8,
                                    const std::unordered_map<std::u8string, std::u8string> &test_list_utf8,
                                    from_u8_type from_u8) {
    SCOPED_TRACE(test_name);

    test_replace_multi_mapped_string_type<string_type, std::map<string_type, string_type> >(
        "std::map", test_text_utf8, test_target_text_utf8, test_list_utf8, from_u8,
        [](std::map<string_type, string_type> &list, const string_type &what, const string_type &with) {
            list[what] = with;
        });
    test_replace_multi_mapped_string_type<string_type, std::unordered_map<string_type, string_type> >(
        "std::unordered_map", test_text_utf8, test_target_text_utf8, test_list_utf8, from_u8,
        [](std::unordered_map<string_type, string_type> &list, const string_type &what, const string_type &with) {
            list[what] = with;
        });
    test_replace_multi_mapped_string_type<string_type, std::vector<std::pair<string_type, string_type> > >(
        "std::vector", test_text_utf8, test_target_text_utf8, test_list_utf8, from_u8,
        [](std::vector<std::pair<string_type, string_type> > &list, const string_type &what, const string_type &with) {
            list.emplace_back(std::pair{with, what});
        });
    test_replace_multi_mapped_string_type<string_type, std::list<std::pair<string_type, string_type> > >(
        "std::list", test_text_utf8, test_target_text_utf8, test_list_utf8, from_u8,
        [](std::list<std::pair<string_type, string_type> > &list, const string_type &what, const string_type &with) {
            list.emplace_back(std::pair{with, what});
        });
}

TEST(cbcore_strings, replace_multi) {
    using namespace std::string_literals;
    using namespace realn;

    const auto test_text_utf8 = u8"źdźbło trawy ścieka w szczękę dżdżownicy równo"s;
    const auto test_target_utf8 = u8"źdźbło trawy kźerśwa w żźwólstwo dżdżownicy równo"s;
    const auto test_list_utf8 = std::unordered_map<std::u8string, std::u8string>{
        {u8"ścieka"s, u8"kźerśwa"s},
        {u8"szczękę"s, u8"żźwólstwo"s}
    };

    test_replace_multi_string_type("std::string",
                                   test_text_utf8,
                                   test_target_utf8,
                                   test_list_utf8,
                                   cb::cast_u8_to_string);

    test_replace_multi_string_type("std::u8string",
                                   test_text_utf8,
                                   test_target_utf8,
                                   test_list_utf8,
                                   [](const std::u8string &item) { return item; });

    test_replace_multi_string_type("std::u16string",
                                   test_text_utf8,
                                   test_target_utf8,
                                   test_list_utf8,
                                   [](const std::u8string &item) { return cb::utf_convert_to_u16(item); });

    test_replace_multi_string_type("std::u32string",
                                   test_text_utf8,
                                   test_target_utf8,
                                   test_list_utf8,
                                   [](const std::u8string &item) { return cb::utf_convert_to_u32(item); });
}
