#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kshitij");
MODULE_DESCRIPTION("Our first dynamically loadable kernel module");
//

static struct proc_dir_entry *custom_proc_node;

// ssize_t (*proc_read)(struct file *, char __user *, size_t, loff_t *);

static ssize_t itashi_read(struct file *file_pointer, char __user *user_space_buffer, size_t count, loff_t *offset) {
    printk("itachi_read ");
    char msg[]="Ack!";
    size_t msg_len = strlen(msg);
    int result;
    if(*offset >= msg_len) return 0;
    result=copy_to_user(user_space_buffer, msg, msg_len);
    *offset +=msg_len;
    return msg_len;
}

struct proc_ops driver_proc_ops = {
    .proc_read = itashi_read
};

static int pyjama_module_init(void)
{
    printk("Kshtij _module_init : entry : \n");

    custom_proc_node = proc_create("itashi_driver",
                                   0,
                                   NULL,
                                   &driver_proc_ops);

    printk("Kshtij _module_init : exit : \n");

    if (custom_proc_node == NULL) {
        printk("driver failed");
        return -1;
    }

    return 0;
}

static void pyjama_module_exit(void)
{
    printk("Kshtij _module_exit : entry : \n");
    proc_remove(custom_proc_node);
    printk("Kshtij _module_exit : exit : \n");
}

module_init(pyjama_module_init);
module_exit(pyjama_module_exit);
