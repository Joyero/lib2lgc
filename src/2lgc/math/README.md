# math

This library contains all you need for math calculation.

# Compare float

Actually you can only compare float and double number.

Use `AlmostEqualUlpsAndAbsF` or `AlmostEqualUlpsAndAbsD` if two numbers are not closed to zero.
Ulps (unit of least precision) is the maximal relative difference (IEEE 754 binary casted to int) so two numbers is the same.
A absolute difference in float/double mode is also used.

Use `AlmostEqualRelativeAndAbsF` or `AlmostEqualRelativeAndAbsD` if two numbers are closed to zero.
The float/double difference is both relative and absolute.

# Hash

Use cryptographic hash if OpenSSL is found. If not, use jbd2. The goal is to use an hash, no matter which one.

