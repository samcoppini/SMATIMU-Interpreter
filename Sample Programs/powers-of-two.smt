100000. Powers of two program in SMATIMU.
100002. Written by Sam Coppini.
100003. Prints out arbitrarily many powers of two.
100004. All steps greater than 100000 are comments.

100005. The step containing the current digit we're operating on.
1. Set cur_digit to 3000.

100006. The value held by the current digit.
2. Set digit_val to 10.

100007. Whether the digit we just doubled overflowed.
100008. 0 = false, 5 = true.
3. Set overflow to 0.

100009. Whether we're printing the number, or doubling it.
100010. 0 = printing, 6 = doubling.
4. Set cur_mode to 0.

100011. The return address from whatever subroutine we just called.
100012. Typically used to un-swap whatever steps we just swapped.
5. Set last_jump to +1.

100013. Jumps to the first digit of the number, and begin printing it out.
6. Swap +0 with 3000.

100014. The first digit of the number.
100015. Sets a variable to the digit's value, and undoes any swaps we just made.
3000. Set digit_val to 10.
3001. Swap -1 with last_jump.

100016. Jump to the next step depending on whether we are currently doubling.
100017. the number, or if we're printing it out.
3002. Swap +0 with +cur_mode.

100018. If we're printing the number, we jump to the digit printing subroutine.
100019. Then move to the next lowest significant digit.
3003. Set last_jump to +1.
3004. Swap last_jump with 1000.
3005. Set cur_digit to -19.
3006. Set last_jump to +1.
3007. Swap +0 with cur_digit.

100020. These steps are reached when we are finished with printing the number.
100021. This prints a newline, and starts the doubling the number.
2991. Set overflow to 0.
2992. Swap cur_digit with last_jump.
2993. Swap +0 through +2 with 9 through 11.
2994. Output this block's position.
2995. Swap -2 through +0 with 2993 through 2995.
2996. Set cur_digit to 3000.
2997. Set cur_mode to 6.
2998. Set last_jump to +1.
2999. Swap +0 with cur_digit.

100022. These are the steps reached for each digit when we're doubling them.
100023. It jumps to the doubling subroutine, then we move to the next most.
100024. significant digit in the number.
3008. Swap +0 with +cur_mode.
3009. Set last_jump to +1.
3010. Swap last_jump with 2000.
3011. Set cur_digit to +3.
3012. Set last_jump to +1.
3013. Swap +0 with cur_digit.

100025. These steps are reached when we finished doubling the number.
100026. It checks if the last digit overflowed, and if so it adds a new digit.
100027. Otherwise, it reverses direction and starts printing the number.
3014. Swap +0 with cur_digit.
3015. Swap +0 with +overflow.
3016. Set cur_mode to 0.
3017. Set cur_digit to -17.
3018. Set last_jump to +1.
3019. Swap +0 with cur_digit.

100028. These steps add a new digit at the start of the number.
100029. They move all the replacement steps forward enough to get out of the.
100030. way for the new digit, then replaces the steps where the steps were.
100031. with the steps necessary for a new digit.
3020. Swap +0 with +overflow.
3021. Swap -7 through +19 with +85 through +111.
3022. Replace -100 with Set digit_val to 10.
3023. Replace -100 with Swap -1 with last_jump.
3024. Replace -100 with Swap +0 with +cur_mode.
3025. Replace -100 with Set last_jump to +1.
3026. Replace -100 with Swap last_jump with 1000.
3027. Replace -100 with Set cur_digit to -19.
3028. Replace -100 with Set last_jump to +1.
3029. Replace -100 with Swap +0 with cur_digit.
3030. Replace -100 with Swap +0 with +cur_mode.
3031. Replace -100 with Set last_jump to +1.
3032. Replace -100 with Swap last_jump with 2000.
3033. Replace -100 with Set cur_digit to +3.
3034. Replace -100 with Set last_jump to +1.
3035. Replace -100 with Swap +0 with cur_digit.

100032. After we've created a new digit, we move the steps back to the end of.
100033. the number, and enters printing mode.
3036. Swap -22 through +4 with -100 through -74.
3037. Set cur_digit to -37.
3038. Set cur_mode to 0.
3039. Set last_jump to +1.
3040. Swap +0 with cur_digit.

100034. The beginning of the printing subroutine.
100035. It gets the value of the current digit, then uses it as an index into.
100036. a table of steps which will print the appropriate value.
999. Swap +0 with 999.
1001. Swap cur_digit with 1002.
1003. Swap cur_digit with 1002.
1004. Swap +0 with +digit_val.

100037. The next 60 lines are just the remainder of the printing subroutine.
100038. They all are the same: Jump to the appropriate location to output the.
100039. correct value, jump back, then jump out of the subroutine.

1005. Swap +0 through +2 with 47 through 49.
1006. Output this block's position.
1007. Swap -2 through +0 with 1005 through 1007.
1008. Swap +0 with 999.

1014. Swap +0 with +digit_val.
1015. Swap +0 through +2 with 48 through 50.
1016. Output this block's position.
1017. Swap -2 through +0 with 1015 through 1017.
1018. Swap +0 with 999.

1024. Swap +0 with +digit_val.
1025. Swap +0 through +2 with 49 through 51.
1026. Output this block's position.
1027. Swap -2 through +0 with 1025 through 1027.
1028. Swap +0 with 999.

1034. Swap +0 with +digit_val.
1035. Swap +0 through +2 with 50 through 52.
1036. Output this block's position.
1037. Swap -2 through +0 with 1035 through 1037.
1038. Swap +0 with 999.

1044. Swap +0 with +digit_val.
1045. Swap +0 through +2 with 51 through 53.
1046. Output this block's position.
1047. Swap -2 through +0 with 1045 through 1047.
1048. Swap +0 with 999.

1054. Swap +0 with +digit_val.
1055. Swap +0 through +2 with 52 through 54.
1056. Output this block's position.
1057. Swap -2 through +0 with 1055 through 1057.
1058. Swap +0 with 999.

1064. Swap +0 with +digit_val.
1065. Swap +0 through +2 with 53 through 55.
1066. Output this block's position.
1067. Swap -2 through +0 with 1065 through 1067.
1068. Swap +0 with 999.

1074. Swap +0 with +digit_val.
1075. Swap +0 through +2 with 54 through 56.
1076. Output this block's position.
1077. Swap -2 through +0 with 1075 through 1077.
1078. Swap +0 with 999.

1084. Swap +0 with +digit_val.
1085. Swap +0 through +2 with 55 through 57.
1086. Output this block's position.
1087. Swap -2 through +0 with 1085 through 1087.
1088. Swap +0 with 999.

1094. Swap +0 with +digit_val.
1095. Swap +0 through +2 with 56 through 58.
1096. Output this block's position.
1097. Swap -2 through +0 with 1095 through 1097.
1098. Swap +0 with 999.

100040. The beginning of the doubling subroutine.
100041. Uses the value of the digit as an index into a table .
1999. Swap +0 with 1999.
2001. Swap cur_digit with 2002.
2003. Swap cur_digit with 2002.
2004. Swap +0 with +digit_val.

2005. Swap +0 with +overflow.
2006. Replace cur_digit with Set digit_val to 0.
2007. Set overflow to 0.
2008. Swap +0 with 1999.
2010. Swap +0 with +overflow.
2011. Replace cur_digit with Set digit_val to 10.
2012. Set overflow to 0.
2013. Swap +0 with 1999.

2014. Swap +0 with +digit_val.
2015. Swap +0 with +overflow.
2016. Replace cur_digit with Set digit_val to 20.
2017. Set overflow to 0.
2018. Swap +0 with 1999.
2020. Swap +0 with +overflow.
2021. Replace cur_digit with Set digit_val to 30.
2022. Set overflow to 0.
2023. Swap +0 with 1999.

2024. Swap +0 with +digit_val.
2025. Swap +0 with +overflow.
2026. Replace cur_digit with Set digit_val to 40.
2027. Set overflow to 0.
2028. Swap +0 with 1999.
2030. Swap +0 with +overflow.
2031. Replace cur_digit with Set digit_val to 50.
2032. Set overflow to 0.
2033. Swap +0 with 1999.

2034. Swap +0 with +digit_val.
2035. Swap +0 with +overflow.
2036. Replace cur_digit with Set digit_val to 60.
2037. Set overflow to 0.
2038. Swap +0 with 1999.
2040. Swap +0 with +overflow.
2041. Replace cur_digit with Set digit_val to 70.
2042. Set overflow to 0.
2043. Swap +0 with 1999.

2044. Swap +0 with +digit_val.
2045. Swap +0 with +overflow.
2046. Replace cur_digit with Set digit_val to 80.
2047. Set overflow to 0.
2048. Swap +0 with 1999.
2050. Swap +0 with +overflow.
2051. Replace cur_digit with Set digit_val to 90.
2052. Set overflow to 0.
2053. Swap +0 with 1999.

2054. Swap +0 with +digit_val.
2055. Swap +0 with +overflow.
2056. Replace cur_digit with Set digit_val to 0.
2057. Set overflow to 5.
2058. Swap +0 with 1999.
2060. Swap +0 with +overflow.
2061. Replace cur_digit with Set digit_val to 10.
2062. Set overflow to 5.
2063. Swap +0 with 1999.

2064. Swap +0 with +digit_val.
2065. Swap +0 with +overflow.
2066. Replace cur_digit with Set digit_val to 20.
2067. Set overflow to 5.
2068. Swap +0 with 1999.
2070. Swap +0 with +overflow.
2071. Replace cur_digit with Set digit_val to 30.
2072. Set overflow to 5.
2073. Swap +0 with 1999.

2074. Swap +0 with +digit_val.
2075. Swap +0 with +overflow.
2076. Replace cur_digit with Set digit_val to 40.
2077. Set overflow to 5.
2078. Swap +0 with 1999.
2080. Swap +0 with +overflow.
2081. Replace cur_digit with Set digit_val to 50.
2082. Set overflow to 5.
2083. Swap +0 with 1999.

2084. Swap +0 with +digit_val.
2085. Swap +0 with +overflow.
2086. Replace cur_digit with Set digit_val to 60.
2087. Set overflow to 5.
2088. Swap +0 with 1999.
2090. Swap +0 with +overflow.
2091. Replace cur_digit with Set digit_val to 70.
2092. Set overflow to 5.
2093. Swap +0 with 1999.

2094. Swap +0 with +digit_val.
2095. Swap +0 with +overflow.
2096. Replace cur_digit with Set digit_val to 80.
2097. Set overflow to 5.
2098. Swap +0 with 1999.
2100. Swap +0 with +overflow.
2101. Replace cur_digit with Set digit_val to 90.
2102. Set overflow to 5.
2103. Swap +0 with 1999.
