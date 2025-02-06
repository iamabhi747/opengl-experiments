#include <custom.h>
#include <string>
#include <ImageIO/ImageIO.h>
#include <CoreServices/CoreServices.h>

void OB_CaptureFrame(std::string filepath, OB_Context *context)
{
    context->captureFrame = true;
    context->screenshotPath = filepath;
}

bool OB_SaveScreenshot(std::string filepath, OB_Context *context)
{
    int width, height;
    glfwGetFramebufferSize(context->window, &width, &height);

    // Allocate memory for the pixel data
    std::vector<GLubyte> pixels(width * height * 4); // 4 components (RGBA)

    // Read pixels from framebuffer
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    // Flip the image vertically since OpenGL has a different coordinate system
    std::vector<GLubyte> flipped(width * height * 4);
    for (int y = 0; y < height; y++) {
        memcpy(&flipped[(height - 1 - y) * width * 4],
               &pixels[y * width * 4],
               width * 4);
    }

    // Save the image to a file
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef bitmapContext = CGBitmapContextCreate(
        flipped.data(),
        width,
        height,
        8,                          // bits per component
        width * 4,                  // bytes per row
        colorSpace,
        kCGImageAlphaPremultipliedLast
    );

    CGImageRef cgImage = CGBitmapContextCreateImage(bitmapContext);
    
    // Create URL reference
    CFStringRef cfFilePath = CFStringCreateWithCString(
        nullptr,
        filepath.c_str(),
        kCFStringEncodingUTF8
    );
    CFURLRef url = CFURLCreateWithFileSystemPath(
        nullptr,
        cfFilePath,
        kCFURLPOSIXPathStyle,
        false
    );
    
    // Create image destination with PNG type
    CFStringRef uttype = CFSTR("public.png");
    CGImageDestinationRef destination = CGImageDestinationCreateWithURL(
        url,
        uttype,
        1,
        nullptr
    );
    
    if (!destination) {
        CGColorSpaceRelease(colorSpace);
        CGContextRelease(bitmapContext);
        CGImageRelease(cgImage);
        CFRelease(cfFilePath);
        CFRelease(url);
        return false;
    }
    
    // Add the image to the destination and finalize
    CGImageDestinationAddImage(destination, cgImage, nullptr);
    bool success = CGImageDestinationFinalize(destination);
    
    // Cleanup
    CGColorSpaceRelease(colorSpace);
    CGContextRelease(bitmapContext);
    CGImageRelease(cgImage);
    CFRelease(destination);
    CFRelease(cfFilePath);
    CFRelease(url);

    return success;
}