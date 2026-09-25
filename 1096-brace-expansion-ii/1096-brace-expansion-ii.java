import java.util.*;

class Solution {
    int pos;

    public List<String> braceExpansionII(String expression) {
        pos = 0;

        Set<String> result = parse(expression);

        List<String> ans = new ArrayList<>(result);
        Collections.sort(ans);

        return ans;
    }

    Set<String> parse(String s) {
        Set<String> result = new HashSet<>();
        Set<String> current = new HashSet<>();
        current.add("");

        while (pos < s.length() && s.charAt(pos) != '}') {

            if (s.charAt(pos) == ',') {
                pos++;

                result.addAll(current);
                current = new HashSet<>();
                current.add("");

            } else if (s.charAt(pos) == '{') {
                pos++;

                Set<String> inside = parse(s);
                pos++; // skip '}'

                current = combine(current, inside);

            } else {
                String ch = String.valueOf(s.charAt(pos));
                pos++;

                Set<String> letter = new HashSet<>();
                letter.add(ch);

                current = combine(current, letter);
            }
        }

        result.addAll(current);

        return result;
    }

    Set<String> combine(Set<String> a, Set<String> b) {
        Set<String> result = new HashSet<>();

        for (String x : a) {
            for (String y : b) {
                result.add(x + y);
            }
        }

        return result;
    }
}