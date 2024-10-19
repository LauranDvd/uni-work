namespace test_web.Models
{
	public class LogText
	{
		public string ChangeType { get; set; } // add / update
		public int AvatarId { get; set; } // for updates
		public string Name { get; set; }
		public int Age { get; set; }
		public string PhotoLink { get; set; }

		public LogText(string changeType, int avatarId, string name, int age, string photoLink)
		{
			ChangeType = changeType;
			AvatarId = avatarId;
			Name = name;
			Age = age;
			PhotoLink = photoLink;
		}
	}
}
