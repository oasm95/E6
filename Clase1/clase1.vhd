library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity clase1 is
    Port ( clk : in STD_LOGIC;
           sw : in STD_LOGIC_VECTOR (3 downto 0);
           led : out STD_LOGIC_VECTOR (3 downto 0));
end clase1;

architecture Behavioral of clase1 is

    constant CLK_1HZ    : natural :=100000000/2;
    constant CLK_2HZ    : natural :=50000000/2;
    constant CLK_10HZ   : natural :=10000000/2;
    constant CLK_10KHZ  : natural :=100000/2;
    constant CLK_1MHZ   : natural :=100/2;
    
------Constantes utilizadas en simulacion    
--    constant CLK_1HZ    : natural :=1000;
--    constant CLK_2HZ    : natural :=500;
--    constant CLK_10HZ   : natural :=100;
--    constant CLK_10KHZ  : natural :=10;
--    constant CLK_1MHZ   : natural :=1;
    
    signal cnt  : integer range 0 to CLK_1HZ;
    signal limite : natural:= CLK_1HZ;
    signal sub_clk : std_logic:='0';
begin

    limit_select : process(sw)
    begin
       case (sw) is
          when "0000" =>
             limite <= CLK_1HZ;
          when "0001" =>
             limite <= CLK_2HZ;
          when "0010" =>
             limite <= CLK_10HZ;
          when "0011" =>
             limite <= CLK_10KHZ;
          when others =>
             limite <= CLK_1MHZ;
       end case;
	end process;
	
	clk_gen :  process (clk)
	begin
	   if rising_edge(clk) then
	
           if cnt < limite then
               cnt <= cnt + 1;
           else 
               cnt<=0;
               sub_clk <= not sub_clk;
           end if;	
       end if;
	end process;


    led(0)<= not sw(0);
    led(1) <= sw(1) and sw(2);
    led(2) <= sw(2) or sw(3);
    led(3) <= sub_clk;
end Behavioral;
