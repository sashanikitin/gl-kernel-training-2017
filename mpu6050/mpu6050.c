#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

static int mpu6050_probe(struct i2c_client *drv_client, const struct i2c_device_id *id)
{
	printk(KERN_INFO "mpu6050: i2c client address is 0x%X\n", drv_client->addr);
	printk(KERN_INFO "mpu6050: i2c driver probed\n");
	return 0;
}

static int mpu6050_remove(struct i2c_client *drv_client)
{
	printk(KERN_INFO "mpu6050: i2c driver removed\n");
	return 0;
}

static const struct i2c_device_id mpu6050_idtable [] = {
	{ "gl_mpu6050", 0 },
	{ }
};

static struct i2c_driver mpu6050_i2c_driver = {
	.driver = {
		.name = "gl_mpu6050",
	},

	.probe = mpu6050_probe ,
	.remove = mpu6050_remove,
	.id_table = mpu6050_idtable,
};

static int mpu6050_init(void)
{
	int ret;

	/* Create i2c driver */
	ret = i2c_add_driver(&mpu6050_i2c_driver);
	if (ret) {
		printk(KERN_ERR "mpu6050: failed to add new i2c driver: %d\n", ret);
		return ret;
	}
	printk(KERN_INFO "mpu6050: i2c driver created\n");

	printk(KERN_INFO "mpu6050: module loaded\n");
	return 0;
}

static void mpu6050_exit(void)
{
	i2c_del_driver(&mpu6050_i2c_driver);
	printk(KERN_INFO "mpu6050: i2c driver deleted\n");

	printk(KERN_INFO "mpu6050: module exited\n");
}

module_init(mpu6050_init);
module_exit(mpu6050_exit);

MODULE_AUTHOR("Andriy.Khulap <andriy.khulap@globallogic.com>");
MODULE_DESCRIPTION("mpu6050 I2C acc&gyro");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");