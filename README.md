# ElectricPiano Report
1. Phân công nhiệm vụ:
   Bùi Quốc Khánh: Viết mã nguồn file python, tìm hiểu cách tạo âm thanh Do, Re, Mi,...
   Nguyễn Văn Diện: Viết mã nguồn file c.
2. Nộp chương trình
3. Giải thích nguyên tắc phát ra các âm thanh Do, Re, Mi,...
  Tần số thạch anh: 11.0592MHz			
  Chu kỳ timer = 1/tần số timer = 12/11.0592=1.085micros
  261.63Hz -> chu kỳ = 0.003822 = 3.822ms			
  Mỗi xung 1.911ms			
  So chu kỳ timer 1.911*1000/1.085=1761			
  65536-1761=63775 -> F91F			
  Tần số thực tế: 1/(số chu kỳ timer * chu kỳ timer * 2) = 261.68Hz -> Sai số không thể tránh khỏi
  Dựa vào công thức trên có thể tính ra toàn bộ giá trị cho các nốt. 
  	Nốt       f			    t			        1/2*t			    Trễ		Gt cần nạp	HEX
    C4			  261.63		0.003822192		0.001911096		1761	63775			  F91F
    C#4/Db4 	277.18		0.003607764		0.001803882		1663	63873			  F981
    D4			  293.66		0.003405299		0.001702649		1569	63967			  F9DF
    D#4/Eb4 	311.13		0.003214091		0.001607045		1481	64055			  FA37
    E4			  329.63		0.003033704		0.001516852		1398	64138			  FA8A
    F4			  349.23		0.002863442		0.001431721		1320	64216			  FAD8
    F#4/Gb4 	369.99		0.002702776		0.001351388		1246	64290			  FB22
    G4			  392			  0.00255102		0.00127551		1176	64360			  FB68
    G#4/Ab4 	415.3		  0.002407898		0.001203949		1110	64426			  FBAA
    A4			  440			  0.002272727		0.001136364		1047	64489			  FBE9
    A#4/Bb4 	466.16		0.002145186		0.001072593		989		64547			  FC23
    B4			  493.88		0.002024783		0.001012392		933		64603			  FC5B
    C5			  523.25		0.001911132		0.000955566		881		64655			  FC8F
    C#5/Db5 	554.37		0.001803849		0.000901925		831		64705			  FCC1
    D5			  587.33		0.00170262		0.00085131		785		64751			  FCEF
    D#5/Eb5 	622.25		0.001607071		0.000803536		741		64795			  FD1B
    E5			  659.25		0.001516875		0.000758438		699		64837			  FD45
    F5			  698.46		0.001431721		0.000715861		660		64876			  FD6C
4,5. Cấu trúc chương trình, mã nguồn đẫ được comment giải thích trong file mã nguồn.
