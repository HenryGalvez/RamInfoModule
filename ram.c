#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/utsname.h>
#include <linux/mm.h>
#include <linux/swapfile.h>
#include <linux/seq_file.h>
#define BUFSIZE  1000

struct sysinfo i;

static struct proc_dir_entry *ent;

static int myread (struct seq_file *buff, void *v){

    printk( KERN_DEBUG "read info\n");
    #define K(x) ((x) << (PAGE_SHIFT - 10))
    si_meminfo(&i);
    seq_printf(buff,"total de ram: %ld MB\nram libre: %ld MB\nporcentaje en uso: %ld\n", K(i.totalram)/1024, K(i.freeram)/1024, ((i.totalram - i.freeram)*100)/i.totalram);
    
    return 0;
}


static int proc_init (struct inode *inode, struct file *file){
    return single_open(file,myread,NULL);
}
    

static const struct file_operations myops ={
    .owner =THIS_MODULE,
    .read=seq_read,
    .release=single_release,
    .open=proc_init,
    .llseek=seq_lseek
};

static int simple_init(void){

    printk(KERN_INFO "ram module init\n");
    ent=proc_create("ram",0,NULL,&myops);
    return 0;
}

static void simple_cleanup(void)
{
    printk(KERN_INFO "ram module end\n");
    proc_remove(ent);

}

module_init(simple_init);
module_exit(simple_cleanup);
