namespace test_web.Models
{
	public class Avatar
	{
		public int Id { get; set; }
		public string Name { get; set; }
		public int Age { get; set; }
		public string PhotoLink { get; set; }

		public Avatar(int id, string name, int age, string photoLink)
		{
			Id = id;
			Name = name;
			Age = age;
			PhotoLink = photoLink;
		}
		
		public Avatar(string name, int age, string photoLink)
		{
			Name = name;
			Age = age;
			PhotoLink = photoLink;
		}
	}
}
