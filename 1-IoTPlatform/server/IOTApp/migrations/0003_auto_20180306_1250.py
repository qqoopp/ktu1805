# Generated by Django 2.0 on 2018-03-06 03:50

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('IOTApp', '0002_auto_20180305_2130'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='tmeasure',
            name='RcvStatus',
        ),
        migrations.AddField(
            model_name='tmeasure',
            name='ValueCd',
            field=models.CharField(max_length=20, null=True, verbose_name='값코드'),
        ),
        migrations.AlterField(
            model_name='tmeasure',
            name='RcvDT',
            field=models.CharField(max_length=20, null=True, verbose_name='수신일시'),
        ),
    ]
