from gi.repository import Gtk, GObject
from math import sqrt


def move_widget(widget, target_x, target_y, speed):
    # get the widget's current position
    fixed = widget.get_parent()
    x= fixed.child_get_property(widget, 'x')
    y= fixed.child_get_property(widget, 'y')

    # calculate its movement
    vector= (target_x-x, target_y-y)
    length= sqrt(vector[0]**2 + vector[1]**2)/speed
    vector= (vector[0]/length, vector[1]/length)
    # make sure the widget doesn't move too far
    x= max(target_x, x+vector[0]) if target_x<x else min(target_x, x+vector[0])
    y= max(target_y, y+vector[1]) if target_y<y else min(target_y, y+vector[1])

    # move the widget
    fixed.move(widget, x, y)

    # return whether or not we've reached the destination
    return target_x!=x or target_y!=y

w= Gtk.Window()

f= Gtk.Fixed()
# create a random image...
i= Gtk.Image.new_from_icon_name('go-next', Gtk.IconSize.BUTTON)
# create some space to move the image
f.set_size_request(800, 800)
f.put(i, 100, 50)
w.add(f)

w.connect('delete-event', Gtk.main_quit)
w.show_all()
# every 1000 milliseconds, move the image closer to the destination
# in this case: destination: (300,300) speed: 10 pixels (per 1000 milliseconds)
GObject.timeout_add(50, move_widget, i, 300, 300, 10)
Gtk.main()