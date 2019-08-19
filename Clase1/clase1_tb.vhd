library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity clase1_tb is
--  Port ( );
end clase1_tb;

architecture Behavioral of clase1_tb is

    component clase1 is 
       Port ( clk : in STD_LOGIC;
            sw : in STD_LOGIC_VECTOR (3 downto 0);
           led : out STD_LOGIC_VECTOR (3 downto 0));
    end component;
    
    signal clk_tb : std_logic:='0';
    signal sw_tb  : std_logic_vector (3 downto 0) :="0000";
    signal led_tb : STD_LOGIC_VECTOR (2 downto 0);
    signal clk_out : std_logic;
begin
    test : clase1 
        port map( 
            clk => clk_tb,
            sw => sw_tb,
            led(2 downto 0) => led_tb,
            led(3) => clk_out        
        );
    
    clk_gen :process
    begin
        clk_tb <= not clk_tb;
        wait for 10ns;
    end process;
    
    process
    variable x: integer range 0 to 15;
    begin
    
        for x in 0 to 15 loop
            sw_tb <= std_logic_vector(to_unsigned(x,4));
            wait for 2 us;
        end loop; 
    end process;
end Behavioral;
