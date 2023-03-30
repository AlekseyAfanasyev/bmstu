Feature: Program should be able to solve biquadratic equation
    In order to make sure the program
    solves equations correctly I have the following
    test scenarios:

    Scenario Outline: Test my function
        Given I have the numbers <A>, <B> and <C>
        When I solve the equation with those numbers
        Then I expect to get <N> roots

    Examples:
        | A | B | C | N |
        | 1 |   2 |  3 | 0 |
        | 2 |   3 |  4 | 0 |
        | 5 |   0 |  0 | 1 |
        | 1 |   4 | -5 | 2 |
        | 2 |  -5 |  3 | 4 |
        | 1 | -25 |  0 | 3 |