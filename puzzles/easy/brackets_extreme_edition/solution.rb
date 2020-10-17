expression = gets.chomp
stack = []
brackets = %w[{ } [ ] ( )]

expression.each_char do |c|
    next unless brackets.include?(c)
    case c
    when '}'
        if stack.last == '{'
            stack.pop
            next
        end
    when ']'
        if stack.last == '['
            stack.pop
            next
        end
    when ')'
        if stack.last == '('
            stack.pop
            next
        end
    end
    stack << c
end

if stack.size == 0
    puts 'true'
else
    puts 'false'
end
