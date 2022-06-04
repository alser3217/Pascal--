program Example;
const
  pi: double = 3.1415926;
var
  num1, num2: integer;
  Res, d: double;
begin
  num1 := 5 / 2;
  write ('num1: ', num1);
  write ('Enter integer: ');
  Read (num2);
  Write ('Num2: ', num2);
  if (num2 > num1) then
  begin
    write ('num2 > num1');
  end
  Res := (num1 + num2);
  if (Res > 0) then
  begin
    Write ('Res > 0: ', Res);
  end
  else
  begin
    if (Res < 0) then
    begin
      write ('Res < 0: ', Res);
    end
    else
    begin
      write ('Res = 0: ', Res);
    end
  end
end.