class Solution { // standard LeetCode class definition
    public String removeOuterParentheses(String s) { // return the string after removing outermost parentheses
        StringBuilder result = new StringBuilder(); // use StringBuilder for efficient string construction
        int depth = 0; // depth tracks how many open parentheses we are currently inside

        for (char c : s.toCharArray()) { // iterate through each character once
            if (c == '(') { // opening parenthesis may be outermost or inner
                if (depth > 0) { // if we're already inside, this is not the outermost opening one
                    result.append(c); // keep inner opening parentheses
                }
                depth++; // now we move one level deeper
            } else { // this must be a closing parenthesis
                depth--; // close the current level first
                if (depth > 0) { // if we're still inside after closing, it was not the outermost closing one
                    result.append(c); // keep inner closing parentheses
                }
            }
        }

        return result.toString(); // convert builder to final answer
    }
}