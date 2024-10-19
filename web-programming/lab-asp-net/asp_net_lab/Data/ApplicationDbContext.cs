using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using asp_net_lab.Models.Domain;

namespace asp_net_lab.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
        public DbSet<asp_net_lab.Models.Domain.Article> Article { get; set; } = default!;
    }
}
