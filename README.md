# ElectricPiano Report

1. Phân công nhiệm vụ:
2. 
   Bùi Quốc Khánh: Viết mã nguồn file python, tìm hiểu cách tạo âm thanh Do, Re, Mi,...
   
   Nguyễn Văn Diện: Viết mã nguồn file c.
   
2. Nộp chương trình
3. 
4. Giải thích nguyên tắc phát ra các âm thanh Do, Re, Mi,...

  Tần số thạch anh: 11.0592MHz
  
  Chu kỳ timer = 1/tần số timer = 12/11.0592=1.085micros
  
  261.63Hz -> chu kỳ = 0.003822 = 3.822ms
  
  Mỗi xung 1.911ms
  
  So chu kỳ timer 1.911*1000/1.085=1761	
  
  65536-1761=63775 -> F91F
  
  Tần số thực tế: 1/(số chu kỳ timer * chu kỳ timer * 2) = 261.68Hz -> Sai số không thể tránh khỏi
  
  Dựa vào công thức trên có thể tính ra toàn bộ giá trị cho các nốt. 
  	![image](https://user-images.githubusercontent.com/58499182/149612373-4ea0fca4-55da-4ca8-ab3e-7dd06d7baa41.png)
    
4,5. Cấu trúc chương trình, mã nguồn đẫ được comment giải thích trong file mã nguồn.
