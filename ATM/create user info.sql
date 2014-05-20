CREATE TABLE user_info(
id int,
name text,
sha1_0 text,
sha1_1 text,
sha1_2 text,
sha1_3 text,
sha1_4 text,
balance real,
enable int,
primary key(id));
insert into user_info values(1,'wang','676e6f35','cfc173f7','3fea9fe2','7699cf81','85397f0c',11111.0,1); 
insert into user_info values(2,'ie','fbdb61c0','9030938f','2e88597f','73a743ea','95fbf416',2.2,1); 
insert into user_info values(3,'rtyu','33bfa196','184e27b5','ae3fb03a','e4f5579e','cbb57ac2',100.0,1); 
insert into user_info values(4,'ggg','7c4a8d09','ca3762af','61e59520','943dc264','94f8941b',1.0,0);